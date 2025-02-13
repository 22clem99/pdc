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

        # Add a handler to trigger event to delete items from node editor
        with dpg.handler_registry():
            dpg.add_key_release_handler(key=dpg.mvKey_Delete, callback=self.callback_delete_item)


    def add_node_to_editor(self, node):
        pass

    def CB_link_node(self, sender, app_data):
        logger.debug(f"Link with parameter: {sender=}, {app_data=}")
        ## Check that the edge can be append
        # A node output can be a multiple edge source
        # but a input can't be a multiple edge destination
        for edge in self.edges:
            if dpg.get_alias_id(edge.input) == app_data[1] or dpg.get_alias_id(edge.output) == app_data[1]:
                logger.info(f"Can't create the edge from {dpg.get_item_alias(app_data[0])} to {dpg.get_item_alias(app_data[1])} because {dpg.get_item_alias(app_data[1])} is not free")
                return 0

        # Create a new edge
        edge = Edge(start_node=dpg.get_item_alias(dpg.get_item_parent(app_data[0])),
                    output=dpg.get_item_alias(app_data[0]),
                    end_node=dpg.get_item_alias(dpg.get_item_parent(app_data[0])),
                    input=dpg.get_item_alias(app_data[1]))

        # Add the edge to the node editor
        edge.add_edge()

        # Add the new edge to the list of edge
        self.edges.append(edge)


    def CB_delink_node(self, sender, app_data):
        pass

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

    def callback_delete_item(self, sender):
        logger.debug(f"Try to delete: {sender=}")
        for selected_node in dpg.get_selected_nodes(NodeEditor.node_editor_name):
            logger.debug(f"Remove the node {selected_node}")
            # Get the node tag to remove
            node_tag = dpg.get_item_alias(selected_node)
            if self.nodes[node_tag].can_be_remove == True:
                # Remove edge between the Node to remove and others
                for edge in self.edges:
                    # If the source or the destination of the edge is the node to delete, delete the edge
                    if edge.start_node == node_tag or edge.end_node == node_tag:
                        logger.debug(f"Remove the edge {edge.tag} because it is linked to the node {node_tag}")
                        # remove edge from the node editor
                        edge.del_edge()

                        # Remove from the edge object from the list
                        self.edges.remove(edge)

                # remove node from the node editor
                self.nodes[node_tag].del_node()

                # Remove from the edge object from the list
                del self.nodes[node_tag]
            else:
                logger.info(f"Can't remove {node_tag}")

        for selected_link in dpg.get_selected_links(NodeEditor.node_editor_name):
            logger.debug(f"Remove the edge {selected_link}")
            # Get the edge tag to remove
            link_tag = dpg.get_item_alias(selected_link)

            # logger.debug(f"Delink with parameter: {sender=}, {app_data=}")
            # Look for the edge to remove
            edge_to_remove = None
            for edge in self.edges:
                if edge.tag == link_tag:
                        edge_to_remove = edge

            if edge_to_remove == None:
                logger.error("Internal error, unable to find the Edge to delink")
                exit(1)

            # remove edge from the node editor
            edge_to_remove.del_edge()

            # Remove from the edge object from the list
            self.edges.remove(edge_to_remove)