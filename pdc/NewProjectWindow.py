import dearpygui.dearpygui as dpg
import gettext
import logging
import xdialog
from ProjectManagerWindow import *
from Settings import *

logger = logging.getLogger(__name__)

class NewProjectWindow:
    def __init__(self) -> None:
        logger.debug("Init NewProjectWindow")
        self.img_name = ""
        self.project_name = ""

    def LaunchNewProjectWindow(self):
        with dpg.window(tag="new_project_creation", no_close=True, no_collapse=True, no_title_bar=True):
            with dpg.group(horizontal=True):
                with dpg.group(horizontal=False, width=150):
                    dpg.add_text(tag="project_name_text", default_value="Enter project name:")
                    dpg.add_button(label=_("Select image"), callback=self.CBSelectionImagePopUp)
                with dpg.group(horizontal=False, width=300):
                    dpg.add_input_text(tag="project_name_text_field")
                    dpg.add_text(tag="image_text", default_value="")
            dpg.add_button(label=_("Finish"), callback=self.CBFinish, pos=[400,50], width=75)

            
    def CBSelectionImagePopUp(self):
        logger.debug("Open Selection Image Pop Up")
        self.img_name = xdialog.open_file(_("Path to file"), filetypes=[(_("Image"), "*.jpeg, *.PNG, *.png")])
        logger.debug(_(f"Open new file {self.img_name}"))
        dpg.set_value("image_text", self.img_name)

    def CBFinish(self):
        logger.debug("Finish setup button pressed")

        self.project_name = dpg.get_value("project_name_text_field")

        # Check that the project name is not empty
        if self.project_name == "":
            # Add a message to give the clue to fill this point
            logger.warning("No project name given")
            return
        # Check that the file name is not empty and exist
        if self.img_name == "":
            # Add a message to give the clue to fill this point
            logger.warning("No image file given")
            return

        logger.debug(f"Finish setup of new project with [Project Name]: {self.project_name}, [Project image path]: {self.img_name}")

        # Hide OpenProjectWindow
        dpg.configure_item("new_project_creation", show=False)

        project_window = ProjectManagerWindow()

        project_window.CreateProject(project_name=self.project_name, img_path=self.img_name)

        project_window.LaunchProjectManagerWindow()