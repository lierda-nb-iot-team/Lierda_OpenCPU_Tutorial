from DoxyDoc import *

##  LwIP Specific doc class based on the base doxydoc class.  LwIP doc building needs to
# be done in a way differently to our modules , so this class includes those changes.
class DoxyDocLwip(DoxyDoc):
    def __init__(self, name, env, workingdir):
        DoxyDoc.__init__(self, name, env, workingdir)

        # For lwip it has its own builder as it is specific to the lwip package.
        # Clone env so that we can then point the main doxy builder to the lwip one
        self.env = self.env.Clone()
        build_dict = self.env['BUILDERS']
        build_dict['Doxygen'] = build_dict['DoxygenLwipDoc']

    def init_options_config(self, cfg_env=None):
        # LwIP has its own doxfile as part of its package.  Just add the ones
        # we need to modify
        self.options_common = DoxyOptions(env=cfg_env)
        self.options_common.set_output(os.path.relpath(self.html_output_path.abspath, self.workingdir))
        if NeulBuildConfig.doxygen_quiet_mode: self.options_common.add_option('QUIET', 'YES')


    def configure_options(self, input_src=None, module_title=None, allexternals=False):
        self.options_common.add_input(input_src)
