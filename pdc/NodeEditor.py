import dearpygui.dearpygui as dpg
import logging
from Node import *
from Edge import *

logger = logging.getLogger(__name__)

class NodeEditor:
    node_editor_name = "Node Editor"
    def __init__(self, parent):
        # Create two input and the output and at them in the node dictionary
        input_node = InputImageNode()
        output_node = OutputImageNode()
        self.nodes = {input_node.tag:input_node, output_node.tag:output_node}

        # Clear this because there is only one input available
        for output in input_node.outputs.values():
            output_edge = output

        # Clear this because there is only one input available
        for input in output_node.inputs.values():
            input_edge = input
        self.edges = [Edge(start_node=input_node.tag, output=output_edge.tag, end_node=output_node.tag, input=input_edge.tag)]

        # By defaut, crerate with an input Node and an output Node
        logger.debug("Display the default node editor")
        with dpg.node_editor(tag=NodeEditor.node_editor_name, label=NodeEditor.node_editor_name, parent=parent, callback=self.CB_link_node, delink_callback=self.CB_delink_node, menubar=True):
            for node in self.nodes.values():
                logger.debug(f"Add node: {node.tag}")
                node.add_node(parent=NodeEditor.node_editor_name)

            for edge in self.edges:
                logger.debug(f"Add edge: {edge.tag}")
                edge.add_edge()

            # Add the menu bar to add node
            with dpg.menu_bar():
                with dpg.menu(label="Add node"):
                    dpg.add_menu_item(label="Resize", callback=self.CBMenuBarResize)
                    dpg.add_menu_item(label="Quantization", callback=self.CBMenuBarQuantization)
                    with dpg.menu(label="Filter"):
                        dpg.add_menu_item(label="Filter", callback=self.CBMenuBarFilter)
                dpg.add_menu_item(label="Help", callback=self.CBMenuHelp)

        # Change position of the two node
        input_node.set_pos((50, 50))
        output_node.set_pos((200, 50))


    def add_node_to_editor(self, node):
        pass

    def CB_link_node(self, sender, app_data):
        logger.debug(f"Link with parameter: {sender=}, {app_data=}")

    def CB_delink_node(self, sender, app_data):
        logger.debug(f"Delink with parameter: {sender=}, {app_data=}")

    def CB_right_click(self, sender, app_data):
        logger.debug(f"Right click with parameter: {sender=}, {app_data=}")

    def CBMenuBarFilter(self, sender, app_data):
        logger.debug(f"Menu bar filter click with parameter: {sender=}, {app_data=}")

    def CBMenuBarQuantization(self, sender, app_data):
        logger.debug(f"Menu bar quantization with parameter: {sender=}, {app_data=}")

    def CBMenuBarResize(self, sender, app_data):
        logger.debug(f"Menu bar resize with parameter: {sender=}, {app_data=}")
        resize_node = ResizeImageNode()
        self.nodes[resize_node.tag] = resize_node
        resize_node.add_node(parent=NodeEditor.node_editor_name)
        resize_node.set_pos((0, 0))

    def  CBMenuHelp(self, sender, app_data):
        logger.debug(f"Menu bar help with parameter: {sender=}, {app_data=}")