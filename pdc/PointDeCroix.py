import dearpygui.dearpygui as dpg
import gettext

# Set the local directory
appname = 'pdc'
localedir = './pdc/locales'
# Set up Gettext
en_i18n = gettext.translation(appname, localedir, fallback=True, languages=['fr'])
# Create the "magic" function
en_i18n.install()

class PointDeCroix:

    def __init__(self):
        dpg.create_context()

    def LaunchPointDeCroix(self):
        '''Start by creating a new windows'''
        dpg.create_viewport(title='Custom Title', width=600, height=300)

        with dpg.window(tag="project_selection", no_close=True, no_collapse=True):
            with dpg.group(horizontal=True):
                dpg.add_button(label=_("open_project"), callback=self.CBOpenProject)
                dpg.add_button(label=_("new_project"),  callback=self.CBNewProject)

        dpg.setup_dearpygui()
        dpg.show_viewport()
        dpg.start_dearpygui()

    def CBOpenProject(self):
        print(_("Open existing project"))

    def CBNewProject(self):
        print(_("New project"))

    def StopPointDeCroix(self):
        dpg.destroy_context()

pdc = PointDeCroix()

pdc.LaunchPointDeCroix()

pdc.StopPointDeCroix()