import dearpygui.dearpygui as dpg
import gettext
import logging
from NewProjectWindow import *
from ProjectManagerWindow import *
from OpenProjectWindow import *
from Settings import *

__name__="pdc"
__version__="0.0.1"

# Set the local directory
appname = __name__
localedir = './pdc/locales'

# Set up Gettext
en_i18n = gettext.translation(appname, localedir, fallback=True, languages=['fr'])

# Create the "magic" function
en_i18n.install()

logger = logging.getLogger(__name__)
logging.basicConfig(encoding='utf-8', level=logging.DEBUG)


class PointDeCroix:
    def __init__(self):
        dpg.create_context()

    def LaunchPointDeCroix(self):
        '''Start by creating a new windows'''
        dpg.create_viewport(title=f"Point de Croix V{__version__}", width=Settings.width, height=Settings.height)

        with dpg.window(tag="project_selection", no_close=True, no_collapse=True, no_title_bar=True):
            with dpg.group(horizontal=True):
                dpg.add_button(label=_("open_project"), callback=self.CBOpenProject)
                dpg.add_button(label=_("new_project"),  callback=self.CBNewProject)

        dpg.setup_dearpygui()
        dpg.show_viewport()
        dpg.start_dearpygui()

    def CBNewProject(self):
        logger.debug(_("New existing project"))
        dpg.configure_item("project_selection", show=False)
        new_project_window = NewProjectWindow()
        new_project_window.LaunchNewProjectWindow()

    def CBOpenProject(self):
        logger.debug(_("Open project"))
        dpg.configure_item("project_selection", show=False)
        open_project_window = OpenProjectWindow()
        open_project_window.LaunchOpenProjectWindow()

    def StopPointDeCroix(self):
        dpg.destroy_context()

pdc = PointDeCroix()

pdc.LaunchPointDeCroix()

pdc.StopPointDeCroix()