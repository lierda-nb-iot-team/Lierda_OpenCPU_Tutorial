import shlex
import fnmatch
import os

class DoxyConfig:
    '''
    Class to read/write in a doxygen config file to/from a dictionary.
    Also includes functionality to determine a list of files doxygen takes as input for HTML and tagfile builds.
    Note: The '@INCLUDE' config paramter is not supported in terms of reading the additional config file and updating
    the dictionary. 
    '''
    def __init__(self, doxyCfgFile=None, rootPath=None):
        self.doxyfile_dict = {}
        self.doxdefaults_dict = {}
        self.doxyCfgFile = doxyCfgFile
        self.rootPath = rootPath

        self._setDefaults()

    def _setDefaults(self):
        # TODO: Can defaults be read in directly from Doxygen...
        defaultDoxygenFilePatterns = '''*.c, *.cc, *.cxx, *.cpp, *.c++, *.java, *.ii, *.ixx, *.ipp, *.i++, *.inl, *.idl, *.ddl, *.odl, *.h, *.hh, *.hxx,
                                      *.hpp, *.h++, *.cs, *.d, *.php, *.php4, *.php5, *.phtml, *.inc, *.m, *.markdown, *.md, *.mm, *.dox, *.py, *.pyw,
                                      *.f90, *.f95, *.f03, *.f08, *.f, *.for, *.tcl, *.vhd, *.vhdl, *.ucf, *.qsf'''

        self.doxdefaults_dict['RECURSIVE'] = 'NO'
        self.doxdefaults_dict['FILE_PATTERNS'] = [pattern.strip() for pattern in defaultDoxygenFilePatterns.split(',')]
        self.doxdefaults_dict['GENERATE_TAGFILE'] = 'NO'
        self.doxdefaults_dict['GENERATE_HTML'] = 'NO'

    def _finaliseDict(self,d):
        '''
        Compress lists to strings where only 1 entry is found unless we explicitly want it left as a list
        to simplify processing later.
        '''
        multiEntryKeys = ['INPUT', 'TAGFILES']
        for k,v in d.iteritems():
            vlen= len(v)
            if vlen == 0:
                d[k]=None
            elif vlen == 1 and k not in multiEntryKeys:
                d[k]=v[0]


    def _add2Dict(self,k,v,k_upd,d):
        if k_upd is False or k not in d:
            d[k]=v
        else:
            d[k].extend(v)


    def _readDoxStream(self, inLex):
        '''
        Reading config file input to capture doxygen config parameters
        First '=' is searched for, previous token that was found is parameter key name
        Once key is found remaining chars are part of value. takes into account mutliple line defs.
        Also 'key += value' is taken in account.
        Some parameters could also include an '=' in the value part. 
        '''
        inLex.whitespace = inLex.whitespace.replace("\n", "")
        inLex.escape = ""
        inLex.wordchars += "*./-:@\\"
        words = inLex.wordchars

        key = None
        key_update = False
        value = list()
        line_extended = False

        token = inLex.get_token()

        while token:
            if key is None:
                if token not in "+=":
                    prev_token = token
                    key_update = False
                elif token == '+':
                    key_update = True
                elif token == '=':
                    key = prev_token
                    prev_token = None
                    if key_update:
                        tag = 'Key update'
                    else:
                        tag = 'Key'
            else:
                if token == '\\':
                    line_extended = True
                    inLex.wordchars += "="
                elif token == '\n':
                    if line_extended is not True:
                        self._add2Dict(key, value, key_update, self.doxyfile_dict)
                        key = None
                        key_update = False
                        value = list()
                        inLex.wordchars = words
                    else:
                        line_extended = False
                else:
                    value.append(token)

            token = inLex.get_token()

        self._finaliseDict(self.doxyfile_dict)


    def readDox(self):
        with open(self.doxyCfgFile, 'r') as doxyCfgFile:
            inLex = shlex.shlex(instream=doxyCfgFile, posix=True)
            self._readDoxStream(inLex)


    def _getOutValStr(self, v):
        '''
        When writing config to file any parameter string entries that include spaces need to have
        the whole string quoted.  This checks and adds quotes if necessary. 
        '''
        if any(c.isspace() for c in str(v)):
            v = '"' + v + '"'
        return v


    def writeDox(self, cfgfile):
        '''
        Writes the doxygen config dictionary to file.  Multiline parameters have each entry on a separate line unless
        key is contained in keepOnSingleLineKeys.
        '''
        keepOnSingleLineKeys = ['ABBREVIATE_BRIEF']

        with open(cfgfile, 'w') as doxyCfgFile:
            dks = self.doxyfile_dict.keys()
            dks.sort()

            for key in dks:
                out = key + " = "
                if self.doxyfile_dict[key] is not None:
                    try:
                        _ = self.doxyfile_dict[key] + ''      # basically tests to determine if value is an iterable or not.
                        out += self._getOutValStr(self.doxyfile_dict[key])
                    except:
                        n = len(out)
                        values = [self._getOutValStr(val) for val in self.doxyfile_dict[key]]

                        if key in keepOnSingleLineKeys:
                            joinstr = ' '
                        else:
                            joinstr = "  \\\n" + ' ' * n

                        out += joinstr.join(values)
                out += "\n"
                doxyCfgFile.write(out)


    def _getDoxInputFiles(self, inEntry, recursive, doxFileFilter):
        '''
        Takes an entry from a config parameter like 'INPUT', which icould be file or dir' and returns
        all files found.  If the recursive seting is enabled it will walk through the subdirs.
        Also, the file patterns config parameter is taken into account
        '''
        if os.path.isfile(inEntry):
            matches = [inEntry]
        else:
            matches = [] 
            for rootdir, dirs, files in os.walk(inEntry):
                for pattern in doxFileFilter:
                    for fn in fnmatch.filter(files, pattern):
                        matches.append(os.path.join(rootdir, fn))
                if not recursive:
                    break

        return matches

    def _getActualKeyValue(self, key):
        '''
        Determines the actual value doxygen will use for a config parameter.
        I.e. is parameter is not in config file the default value is used.
        Note: Ideally it may be better to autocreate if possible the defaults from
        running doxygen and create a third dictionary containing a merge of the defaults
        and those read in from the config file.  Then this function and dictionary would not
        need to be updated and maintained.
        '''
        value = None
        if key not in self.doxyfile_dict or self.doxyfile_dict[key] is None:
            if key in self.doxdefaults_dict:
                value = self.doxdefaults_dict[key]
        else:
            value = self.doxyfile_dict[key]

        return value

    def getSources(self):
        '''
        This should analyse the configuration and determine all files doxygen will use as input/src.
        Note: This currently does not handle all cases/types of docs that can be created.
        '''
        allSrcFiles = set()
        keysToAdd = []

        if self._getActualKeyValue('RECURSIVE') == 'NO':
            recursive = False
        else:
            recursive = True

        filePatterns = self._getActualKeyValue('FILE_PATTERNS')

        key = 'INPUT'
        if key in self.doxyfile_dict and self.doxyfile_dict[key] is not None:
            for entry in self.doxyfile_dict[key]:
                entry = os.path.join(self.rootPath,entry)
                allSrcFiles.update(self._getDoxInputFiles(entry, recursive, filePatterns))

        # Add Tag File Srcs
        if self._getActualKeyValue('GENERATE_TAGFILE') != 'YES':
            key = 'TAGFILES'
            if key in self.doxyfile_dict and self.doxyfile_dict[key] is not None:
                for entry in self.doxyfile_dict[key]:
                    tag = entry.split('=')
                    allSrcFiles.add(tag[0].strip())

            keysToAdd.append('PROJECT_LOGO')

        #Add other html files
        if self._getActualKeyValue('GENERATE_HTML') != 'YES':
            keysToAdd.extend(['HTML_HEADER','HTML_FOOTER','HTML_EXTRA_STYLESHEET','HTML_EXTRA_FILES'])

        for key in keysToAdd:
            if key in self.doxyfile_dict and self.doxyfile_dict[key] is not None:
                try:
                    _ = self.doxyfile_dict[key] + ''      # basically tests to determine if value is an iterable or not.
                    allSrcFiles.add(self.doxyfile_dict[key])
                except:
                    for entry in self.doxyfile_dict[key]:
                        allSrcFiles.add(self.doxyfile_dict[key])
        allSrcFilesList = list(allSrcFiles)
        allSrcFilesList.sort()

        return allSrcFilesList
