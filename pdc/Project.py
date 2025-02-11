import logging
import os
import shutil
import uuid
import dearpygui.dearpygui as dpg

# Get logger object
logger = logging.getLogger(__name__)

class Project:
    __root_project_dir = "./.pdc/"
    __default_img_name = "img"
    default_texture_image_name = "texture_img_base"

    def __init__(self, img_path="", project_name="", project_file=""):
        if project_file != "":
            # TODO open the file and parse all
            logger.warning("TODO: add to parse an existing project")
        else:
            self.project_file = project_file
            self.project_name = project_name
            self.img_path = img_path
            _, self.img_ext = os.path.splitext(self.img_path)
            logger.debug(f"Create a new project with [Project Name]: {self.project_name} [Path image] {self.img_path} [Image Extension]: {self.img_ext}")

    def setup_work_dir(self):
        # Create the PDC work directory
        os.makedirs(Project.__root_project_dir, exist_ok=True)

        # Create the project
        self.project_workspace = Project.__root_project_dir + self.project_name.replace(' ', '_')
        try:
            os.mkdir(self.project_workspace)
        except FileExistsError:
            # Append a random string to create a unique workspace
            # Lengh of the random string
            length = 8
            self.project_workspace = self.project_workspace + "_" + str(uuid.uuid4()).replace('-', '')[:length]
            os.mkdir(self.project_workspace)

        logger.debug(f"Create a new workspace at \"{self.project_workspace}\"")

        # Copy the image to the local work space
        self.working_image = self.project_workspace + "/" + Project.__default_img_name + self.img_ext
        shutil.copyfile(self.img_path, self.working_image)

        # Load default image as texture
        self.width_img_base, self.height_img_base, self.channels_img_base, self.data_img_base = dpg.load_image(self.working_image)
        with dpg.texture_registry(show=False):
            dpg.add_static_texture(width=self.width_img_base,  height=self.height_img_base, default_value=self.data_img_base, tag=Project.default_texture_image_name)


        logger.debug(f"Copy work image from \"{self.img_path}\" to \"{self.working_image}\"")

    def __str__(self) -> str:
        pass

    def save_project(self):
        pass

