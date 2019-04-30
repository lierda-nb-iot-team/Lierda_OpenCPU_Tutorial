from copy import copy, deepcopy

## DoxyOptions Class handles all used Doxygen options.  It stores all options in a dictionary
# that is used when creating the final config file.
class DoxyOptions:
    ## 
    #  @param    default_dict    If provided it will be the first set of data that is added to the options dictionary.
    #  @param    override_dict   If provided the data within this dictionary is added to or existing keys are updated
    #                            in the options dictionary. Note: The data values associated with these keys are subsequently
    #                            read only and cannot be updated.  Typically, this us used to have target specific overides that
    #                            can be defined in the targets list.
    #  @param    proj_name       A project name string to use for the doxygen option PROJECT_NAME.  Note: overide_dict value takes precedence. 
    #  @param    proj_brief      A project brief string to use for the doxygen option PROJECT_BRIEF.  Note: overide_dict value takes precedence. 
    #  @param    proj_num        A project number string to use for the doxygen option PROJECT_NUMBER.  Note: overide_dict value takes precedence.
    #  @param    name            Name of module this doxy option object is associated with.
    #  @param    env             Env variable to associate this doxygen options dictionary with.
    def __init__(self, name=None, env=None, proj_name=None, proj_brief=None, proj_num=None, default_dict=None, override_dict=None):
        self.options_dict = {}
        self.name = name
        self.name_str = ''
        if name: self.name_str = '(' + self.name + ')'

        if default_dict: self.options_dict.update(default_dict)
        self.overide_dict_keys = []
        if override_dict:
            self.overide_dict_keys = override_dict.keys()
            self.options_dict.update(override_dict)

        if env: self.add_to_env(self,env)

        self.set_proj_number(proj_num)
        self.set_proj_brief(proj_brief)

    def __str__(self):
        if len(self.options_dict) == 0:
            print_str = "DoxyOptions Dictionary" + self.name_str + ": None\n"
        else:
            print_str = "DoxyOptions Dictionary" + self.name_str + ":\n"
            for key in sorted(self.options_dict.keys()):
                key_str = str(key) + ': ' + str(self.options_dict[key])
                print_str += key_str + "\n"
        return print_str

    def add_to_env(self,env):
        env['DOXY_OPTIONS'] = self.options_dict

    def copy(self):
        # make a copy of this object  
        copy_obj = copy(self)
        copy_obj.overide_dict_keys = copy(self.overide_dict_keys)
        copy_obj.options_dict = deepcopy(self.options_dict)
        return copy_obj

    ## Adds items into the options dictionary under its key.  Items stored
    # in the dictionary are stored as a list.
    #
    # @param key : key under which to add or append items
    # @param items : Can be a single item or an iterable object of items.
    # @param reset: True/False, indicates if existing key in dictionary should bve overwritten or not. 
    def _add_to_key_list (self, key, items, reset):
        if items:
            if key not in self.options_dict or reset:
                items_set = set(items)
            else:
                items_set = set(self.options_dict[key])
                try:
                    _ = items + ''      # basically tests to determine if files_or_dirs is an iterable or not.
                    items_set.add(items)
                except:
                    items_set.update(items)

            self.options_dict[key] = list(items_set)    #set type ensures unique entried, stared as list as doxyoptions pkg uses lists.

    def add_input(self, files_or_dirs, reset=False):
        key = 'INPUT'
        self._add_to_key_list(key, files_or_dirs, reset)

    def set_output(self, path):
        self.add_option('OUTPUT_DIRECTORY', path)

    def set_proj_brief(self, brief):
        if brief: self.add_option('PROJECT_BRIEF', brief)

    def set_proj_number(self, projnum):
        if projnum: self.add_option('PROJECT_NUMBER', projnum)

    def add_option(self, key, value):
        if key not in self.overide_dict_keys:
            self.options_dict[key] = value

    def add_input_tagfile_entries(self, tags, reset=False):
        key ='TAGFILES'
        self._add_to_key_list (key, tags, reset)

    def add_include_paths(self, incs, reset=False):
        key ='INCLUDE_PATH'
        self._add_to_key_list(key, incs, reset)
 
    def set_output_tagfile(self, tagfile, tagfile_only=True):
        if tagfile:
            key_tag = 'GENERATE_TAGFILE'
            key_html = 'GENERATE_HTML'

            self.options_dict[key_tag] = tagfile
            if tagfile_only:    self.options_dict[key_html] = 'NO'

