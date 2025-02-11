from abc import ABC, abstractmethod
import random
import dearpygui.dearpygui as dpg
import logging
from common.Singleton import *

from Input import *
from Output import *

logger = logging.getLogger(__name__)

class HandlerNode(Singleton):
    def __new__(cls):
        logger.debug(f"Get {cls} singleton")
        if not hasattr(cls, 'instance'):
            logger.debug(f"Create a {cls} instance")
            cls.instance = super(Singleton, cls).__new__(cls)
            cls.instance.tag = "Handler node"
            dpg.add_item_handler_registry(tag=cls.instance.tag)
            dpg.add_item_clicked_handler(parent=cls.instance.tag, callback=Node.CB_right_click)
        return cls.instance


class Node(ABC):
    def __init__(self, name="", inputs=None, outputs=None, can_be_remove=True):
        self.tag = name + "_" + str(random.randint(0, 50000))
        self.name = name
        self.can_be_remove = can_be_remove

        # Create dict with all inputs
        logger.debug("Create dict for inputs")
        self.inputs = {}
        for input in inputs:
            logger.debug(f"Add input: {input.tag}")
            self.inputs[input.tag] = input

        # Create dict with all outputs
        logger.debug("Create dict for outputs")
        self.outputs = {}
        for output in outputs:
            logger.debug(f"Add output: {output.tag}")
            self.outputs[output.tag] = output

        self.handler_node = HandlerNode()

        logger.debug(f"Add new node [Name]: {self.name}, [Tag]: {self.tag}, [Inputs]: {self.inputs}, [Outputs]: {self.outputs}")

    def add_node(self, parent):
        logger.debug(f"Add node \"{self.tag}\"to node editor ({parent=}) with name {self.name=}")

        dpg.add_node(tag=self.tag, label=self.name, parent=parent)
        logger.debug("Add inputs")
        for input in self.inputs.values():
            logger.debug(f"Add input \"{input.tag}\"to node (parent={self.tag}) with name {input.name}")
            input.add_input_to_node(parent=self.tag)
        logger.debug("Add outputs")
        for output in self.outputs.values():
            logger.debug(f"Add output \"{output.tag}\"to node editor")
            output.add_output_to_node(parent=self.tag)

        # Add right click callback
        logger.debug(f"Bind handler to {self.tag} to {self.handler_node.tag}")
        dpg.bind_item_handler_registry(self.tag, self.handler_node.tag)

    def set_pos(self, pos):
        logger.debug(f"Set position of node {self.tag}")
        self.pos = pos
        dpg.set_item_pos(self.tag, pos)

    @abstractmethod
    def compute_outputs(self):
        pass

    def CB_right_click(self, sender, app_data):
        logger.debug(f"Right click with parameter: {sender=}, {app_data=}")



class InputImageNode (Node):
    def __init__(self):
        return super().__init__(name="Input node",
                                inputs=[],
                                outputs=[ImageOutput()],
                                can_be_remove=False)

    def add_node(self, parent):
        super().add_node(parent=parent)

    def compute_outputs(self):
        pass

class OutputImageNode (Node):
    def __init__(self):
        super().__init__(name="Output node",
                         inputs=[ImageInput()],
                         outputs=[],
                         can_be_remove=False)

    def add_node(self, parent):
        super().add_node(parent=parent)

    def compute_outputs(self):
        pass

class ResizeImageNode(Node):
    def __init__(self):
        super().__init__(name="Resize node",
                         inputs=[ImageInput()],
                         outputs=[ImageOutput()],
                         can_be_remove=True)

    def add_node(self, parent):
        super().add_node(parent=parent)

    def compute_outputs(self):
        pass