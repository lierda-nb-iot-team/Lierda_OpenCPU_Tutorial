import os
import platform
import subprocess
import errno
import traceback
import SCons.Errors


_root = os.path.join(os.path.dirname(os.path.dirname(os.path.dirname(os.path.realpath(__file__)))), "build_scons")

def _get_description_from_git():
    try:
        git_string = subprocess.check_output(["git", "describe", "--tags", "--first-parent", "--dirty", "--always"]).strip()
    except:
        # The SDK builds do not require Git to be installed.
        git_string = "UNKNOWN"
    return git_string

def get_git_hash(ARGUMENTS):
    if "GIT_DESCRIPTION" in ARGUMENTS:
        description = ARGUMENTS["GIT_DESCRIPTION"]
    else:
        description = _get_description_from_git()
        
    desc_list = description.split("-")
    
    if desc_list[-1] == "dirty":
        git_hash = desc_list[-2] + "-dirty"
    else:
        git_hash = desc_list[-1]

    return (git_hash, description)
    
def read_string(filename):
    filepath = os.path.join(_root, filename)
    with open(filepath) as f:
        return f.read()


def _update_string(filename, string):
    # update version info file if changed
    
    filepath = os.path.join(_root, filename)
    
    if not os.path.exists(_root):
        os.makedirs(_root)
    
    existing_string = read_string(filename) if os.path.exists(filepath) else ''

    if existing_string != string:
        print "Updating", filename, "file"
        with open(filepath, "w") as f:
            f.write(string)
            

def update_version(ARGUMENTS):
    (git_hash, description) = get_git_hash(ARGUMENTS)
    
    if "VERSION_STRING" in ARGUMENTS:
        version_string = ARGUMENTS["VERSION_STRING"]
    else:
        version_string = description + "-" + platform.node()
    
    # Limit to what the target code can handle - must fit in a 48 char array so it has a maximum of 47 characters.
    # Magic number shared with source code in the build_version module!
    version_string = version_string[:47]
    
    print "Using version string:", version_string
    print "Using git hash:", git_hash
                
    _update_string("VERSION_STRING", version_string)
    _update_string("GIT_HASH", git_hash)
