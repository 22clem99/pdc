import dearpygui.dearpygui as dpg
import random
import logging

logger = logging.getLogger(__name__)

class Edge():
    def __init__(self, start_node, output,  input, end_node):
        self.start_node = start_node
        self.output = output
        self.end_node = end_node
        self.input = input
        self.tag = "Edge_" + start_node + "_to_" + end_node + str(random.randint(0, 50000))

    def add_edge(self):
        logger.debug(f"Create edge with attr1={self.output}, attr2={self.input}, tag={self.tag}, parent={self.start_node}")
        dpg.add_node_link(self.output, self.input, tag=self.tag, parent="Node Editor")