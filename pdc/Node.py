from abc import ABC, abstractmethod
import random
import dearpygui.dearpygui as dpg
import logging
from common.Singleton import *

from Input import *
from Output import *

logger = logging.getLogger(__name__)

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

    def del_node(self):
        logger.debug(f"Delete node \"{self.tag}\"")
        dpg.delete_item(self.tag)

    def set_pos(self, pos):
        logger.debug(f"Set position of node {self.tag}")
        self.pos = pos
        dpg.set_item_pos(self.tag, pos)

    @abstractmethod
    def compute_outputs(self):
        pass

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