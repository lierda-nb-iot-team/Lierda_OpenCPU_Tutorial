#===============================================================================
# @brief    Script file
# Copyright (c) 2016 NEUL LIMITED
#===============================================================================

'''
Read in an elf file and generate a 'du' output for it.
'''
from __future__ import print_function
from collections import OrderedDict
import subprocess
import re
import argparse

if __name__ == '__main__':
    parser = argparse.ArgumentParser(description='Generate du output from an elf file')
    parser.add_argument('elf', metavar="ELF", help="ELF file to parse")
    parser.add_argument('--nm', default=["arm-none-eabi-nm"], nargs=1, help="Name of binutils nm utility")
    args = parser.parse_args()

    # Get nm and elf filenames from command line args    
    nm = args.nm[0]
    elf = args.elf

    # build command line and run nm    
    cmd = nm + ' -l -A -t x -f sysv -S ' + elf
    p = subprocess.Popen(cmd.split(), stdin=subprocess.PIPE, stdout=subprocess.PIPE)
    stdout, stderr = p.communicate()
    return_code = p.wait()
    if (return_code != 0):
        raise StandardError(nm + " returned: " + str(return_code))

    # parse the output
    line_count = 0
    line_match = 0
    symbol_type = OrderedDict()
    
    # Convert stdout from bytes to a string
    stdoutstr = stdout.decode("utf-8")
    
    # Loop over each line in the string
    for line in iter(stdoutstr.splitlines()):
        line_count = line_count + 1

        sl = line.split("|")
        if (len(sl) == 7):
            elfsym = re.match(r'^(.*):([^\s]*)', sl[0])
            if elfsym:
                elf = elfsym.group(1)
                symbol = elfsym.group(2)
                
                if (len(sl[1].strip())):
                    location = int(sl[1], 16)
                else:
                    location = 0

                c = sl[2].strip()
                t = sl[3].strip()
                if (len(sl[4].strip())):
                    size = int(sl[4], 16)
                else:
                    size = 0
                u2 = sl[5]        
                segmentfileline = re.match(r'([^\t]*)\t(.*):([^\|]*)', sl[6])
                if segmentfileline:
                    segment = segmentfileline.group(1)
                    src_file = segmentfileline.group(2)
                    src_file_line = int(segmentfileline.group(3))
                    if segment not in symbol_type:
                        symbol_type[segment] = list()
                    symbol_type[segment].append((src_file, symbol, size))
                    line_match = line_match + 1
#                else:
#                    print("segmentfileline failed on: '" + sl[6] + "' from: '" + line + "'")
#            else:
#                print("elfsym failed on: '" + sl[0] + "' from: '" + line + "'")
#        else:
#            print("len failed on : '" + line + "'")                                


    # Find common filename prefix string from all input files
    initPrefix = True
    for segment in symbol_type:
        symbol_type[segment].sort(key = lambda x:x[0])

        for symbol in symbol_type[segment]:
            filename = symbol[0];
            if initPrefix == True:
                prefix = filename
                initPrefix = False
            
            if len(filename) < len(prefix):
                prefix = prefix[:len(filename)]
            if not prefix:
                break
            
            for i in range(len(prefix)):
                if prefix[i] != filename[i]:
                    prefix = prefix[:i]
                    break

    # Loop through displaying each line and totals
    segmentTotal = 0
    # Loop over each segment
    for segment in symbol_type:
        filenameTotal = 0                
        currFilename = ''
        
        # Loop over each symbol in segment
        for symbol in symbol_type[segment]:
            filename = symbol[0]
            sym = symbol[1]
            size = symbol[2]
            
            # strip prefix from start of filename
            if (prefix):
                filename = filename.replace(prefix, '', 1)
            # convert \\ to / in filename
            filename = filename.replace('\\', '/')
            
            if filename != currFilename:
                #if currFilename:
                    #print('%(sz)-8u./%(segment)s/%(file)s' % {'sz': filenameTotal, 'segment': segment,'file': currFilename})
                currFilename = filename
                filenameTotal = 0
            filenameTotal = filenameTotal + size
            segmentTotal = segmentTotal + size    
            # print line for filename/function            
            print('%(sz)-8u./%(segment)s/%(file)s/%(sym)s' % {'sz': size, 'segment': segment, 'file': filename, 'sym': sym})
            
        # print total for filename (last one)
        #print('%(sz)-8u./%(segment)s/%(file)s' % {'sz': filenameTotal, 'segment': segment, 'file': currFilename})
        
        # print total for segment
        #print '%(sz)-8u./%(segment)s' % {'sz': segmentTotal, 'segment': segment}
        segmentTotal = 0
        #print(str(symbol[2]) + " " + segment + "/" + symbol[0].replace('\\', '/') + "/" + symbol[1]) 
    
    print("done. Lines: " + str(line_count) + ", Matches: " + str(line_match))