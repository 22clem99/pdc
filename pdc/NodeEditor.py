import dearpygui.dearpygui as dpg
import logging
from Node import *
from Edge import *

logger = logging.getLogger(__name__)

class NodeEditor:
    node_editor_name = "Node Editor"
    def __init__(self, parent):
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
        with dpg.node_editor(label=NodeEditor.node_editor_name, parent=parent, callback=self.CB_link_node, delink_callback=self.CB_delink_node):
            for node in self.nodes.values():
                logger.debug(f"Add node: {node.tag}")
                node.add_node(parent=NodeEditor.node_editor_name)

            for edge in self.edges:
                logger.debug(f"Add edge: {edge.tag}")
                edge.add_edge()

    def add_node_to_editor(self, node):
        pass

    def CB_link_node(self, sender, app_data):
        logger.debug(f"Link with parameter: {sender=}, {app_data=}")

    def CB_delink_node(self, sender, app_data):
        logger.debug(f"Link with parameter: {sender=}, {app_data=}")