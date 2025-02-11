import dearpygui.dearpygui as dpg
import gettext
import logging
from common.Singleton import *
from Project import *
from Settings import *
from NodeEditor import *

logger = logging.getLogger(__name__)

class ProjectManagerWindow(Singleton):
    def OpenProject(self, path_pdc_project):
        # TODO: Open Project
        pass

    def CreateProject(self, img_path, project_name):
        logger.debug("Create new Project")
        self.project = Project(img_path=img_path, project_name=project_name)
        self.project.setup_work_dir()

    def LaunchProjectManagerWindow(self):
        with dpg.window(tag=f"{self.project.project_name}", pos=[0, 0], width=Settings.width, height=Settings.height, autosize=False, no_move=True, menubar=True, no_title_bar=True):
            # Menu Bar
            with dpg.menu_bar():
                with dpg.menu(label="File"):
                    dpg.add_menu_item(label="Save", callback=self.CBMenuBarSave)
                    dpg.add_menu_item(label="Save As", callback=self.CBMenuBarSaveAs)
                with dpg.menu(label="View"):
                    dpg.add_menu_item(label="Brodery view", callback=self.CBViewBroderyView)
                dpg.add_menu_item(label="Help", callback=self.CBMenuHelp)

            # Preview
            with dpg.group(tag="group horizontal project manager", horizontal=True):
                with dpg.group(tag="group vertical preview", width=(Settings.width/2), height=-1):
                    with dpg.subplots(2, 1, label="Images Preview", width=-1, height=-1, link_all_x=True, link_all_y=True):
                        # Preview none modified image
                        with dpg.plot(label="Images displayed", no_title=True, crosshairs=False, equal_aspects=True):
                            dpg.add_plot_axis(dpg.mvXAxis, label="x axis not modified", no_label=True, no_gridlines=True, no_tick_marks=True, no_tick_labels=True)
                            dpg.add_plot_axis(dpg.mvYAxis, label="y axis not modified", no_label=True, no_gridlines=True, no_tick_marks=True, no_tick_labels=True)
                            dpg.add_image_series(parent=dpg.last_item(), texture_tag=Project.default_texture_image_name, bounds_min=[0, 0], bounds_max=[self.project.width_img_base, self.project.height_img_base])

                        # Preview modified image
                        with dpg.plot(label="Images displayed", no_title=True, crosshairs=False, equal_aspects=True):
                            dpg.add_plot_axis(dpg.mvXAxis, label="x axis modified", no_label=True, no_gridlines=True, no_tick_marks=True, no_tick_labels=True)
                            dpg.add_plot_axis(dpg.mvYAxis, label="y axis modified", no_label=True, no_gridlines=True, no_tick_marks=True, no_tick_labels=True)
                            dpg.add_image_series(parent=dpg.last_item(), texture_tag=Project.default_texture_image_name, bounds_min=[0, 0], bounds_max=[self.project.width_img_base, self.project.height_img_base])

                with dpg.group(tag="group vertical node editor", height=-1, width=-1):
                    # Create the node editor here
                    node_editor = NodeEditor(parent="group vertical node editor")

    def CBMenuBarSave(self):
        logger.warning("TODO")

    def CBMenuBarSaveAs(self):
        logger.warning("TODO")

    def CBViewBroderyView(self):
        logger.warning("TODO")

    def CBMenuHelp(self):
        logger.warning("TODO")
