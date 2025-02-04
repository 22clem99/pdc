import dearpygui.dearpygui as dpg
import gettext
import logging
from common.Singleton import *
from Project import *
from Settings import *

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
            with dpg.group(horizontal=True):
                with dpg.group(horizontal=False, width=(Settings.width/2)):
                    # Preview non modified image
                    with dpg.plot(label="Images displayed", no_title=True, crosshairs=False, equal_aspects=True):
                        dpg.add_plot_axis(dpg.mvXAxis, label="x axis", no_label=True, no_gridlines=True, no_tick_marks=True, no_tick_labels=True)
                        dpg.add_plot_axis(dpg.mvYAxis, label="y axis not modified", no_label=True, no_gridlines=True, no_tick_marks=True, no_tick_labels=True)
                        dpg.add_image_series(parent=dpg.last_item(), texture_tag=Project.default_texture_image_name, bounds_min=[0, 0], bounds_max=[self.project.width_img_base, self.project.height_img_base])
                        dpg.add_plot_axis(dpg.mvYAxis2, label="y axis modified", no_label=True, no_gridlines=True, no_tick_marks=True, no_tick_labels=True)
                        dpg.add_image_series(parent=dpg.last_item(), texture_tag=Project.default_texture_image_name, bounds_min=[0, 0], bounds_max=[self.project.width_img_base, self.project.height_img_base])


    def CBMenuBarSave(self):
        logger.warning("TODO")

    def CBMenuBarSaveAs(self):
        logger.warning("TODO")

    def CBViewBroderyView(self):
        logger.warning("TODO")

    def CBMenuHelp(self):
        logger.warning("TODO")
