import dearpygui.dearpygui as dpg

class Edge():
    def __init__(self, start, end):
        self.start = start
        self.end = end

    def add_edge(self, parent):
        dpg.add_node_link(self.start, self.end, parent=parent)