import dearpygui.dearpygui as dpg
import gettext
import logging
import xdialog
from ProjectManagerWindow import *
from Settings import *

logger = logging.getLogger(__name__)

class OpenProjectWindow:
    def __init__(self) -> None:
        logger.debug("Init OpenProjectWindow")
        self.img_name = ""

    def LaunchOpenProjectWindow(self):
        with dpg.window(tag="open_project_creation", no_close=True, no_collapse=True, no_title_bar=True):
            with dpg.group(horizontal=True):
                with dpg.group(horizontal=False, width=150):
                    dpg.add_button(label=_("Select project file"), callback=self.CBSelectionImagePopUp)
                with dpg.group(horizontal=False, width=300):
                    dpg.add_text(tag="image_text", default_value="")
            dpg.add_button(label=_("Finish"), callback=self.CBFinish, pos=[400,50], width=75)

            
    def CBSelectionImagePopUp(self):
        logger.debug("Open Selection Point De Croix project Pop Up")
        self.img_name = xdialog.open_file("Path to file", filetypes=[("Point De Croix Project File", "*.pdc")])
        logger.debug(f"Open new file {self.img_name}")
        dpg.set_value("image_text", self.img_name)

    def CBFinish(self):
        logger.debug("Finish setup button pressed")

        self.project_name = dpg.get_value("project_name_text_field")

        # Check that the project name is not empty
        if self.project_name == "":
            # Add a message to give the clue to fill this point
            logger.warning("No project name given")
            return
        
        logger.debug(f"Finish open of new project with [Project File Name]: {self.img_name}")
        
        # Hide OpenProjectWindow
        dpg.configure_item("open_project_creation", show=False)

        project_window = ProjectManagerWindow()

        project_window.OpenProject()
        
        project_window.LaunchProjectManagerWindow()