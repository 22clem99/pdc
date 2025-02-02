import dearpygui.dearpygui as dpg

class PointDeCroix:

    def __init__(self):
        dpg.create_context()

    def LaunchPointDeCroix(self):
        '''Start by creating a new windows'''
        dpg.create_viewport(title='Custom Title', width=600, height=300)

        with dpg.window(tag="project_selection", no_close=True):
            dpg.add_button(label="Open project", callback=self.CBOpenProject)
            dpg.add_button(label="New project",  callback=self.CBNewProject)

        with dpg.window(tag="project_selection2", no_close=True):
            dpg.add_button(label="Open project2", callback=self.CBOpenProject)
            dpg.add_button(label="New project2",  callback=self.CBNewProject)


        dpg.setup_dearpygui()
        dpg.show_viewport()
        dpg.start_dearpygui()

    def CBOpenProject(self):
        print("Open existing project")

    def CBNewProject(self):
        print("New project")

    def StopPointDeCroix(self):
        dpg.destroy_context()

pdc = PointDeCroix()

pdc.LaunchPointDeCroix()

pdc.StopPointDeCroix()