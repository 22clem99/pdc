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
        self.edges = [Edge(input_node.tag, output_node.tag)]

        # By defaut, crerate with an input Node and an output Node
        with dpg.node_editor(label=NodeEditor.node_editor_name, parent=parent, callback=self.CB_link_node, delink_callback=self.CB_delink_node):
            for node in self.nodes.values():
                node.add_node(parent=NodeEditor.node_editor_name)

            for edge in self.edges:
                edge.add_edge(parent=NodeEditor.node_editor_name)

    def add_node_to_editor(self, node):
        pass

    def CB_link_node(self, sender, app_data):
        logger.debug(f"Link with parameter: {sender=}, {app_data=}")

    def CB_delink_node(self, sender, app_data):
        logger.debug(f"Link with parameter: {sender=}, {app_data=}")