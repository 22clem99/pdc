from abc import ABC, abstractmethod
import random
import dearpygui.dearpygui as dpg
import logging

from Input import *
from Output import *

logger = logging.getLogger(__name__)

class Node(ABC):
    def __init__(self, name="", inputs=None, outputs=None) -> str:
        super().__init__()
        self.tag = name + "_" + str(random.randint(0, 50000))
        self.name = name
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
        logger.debug(f"Add node \"{self.tag}\"to node editor")
        with dpg.node(tag=self.tag, label=self.name, parent=parent):
            for input in self.inputs.values():
                logger.debug(f"Add input \"{input.tag}\"to node")
                input.add_input_to_node(parent=self.tag)
            for output in self.outputs.values():
                logger.debug(f"Add output \"{output.tag}\"to node editor")
                output.add_output_to_node(parent=self.tag)


    @abstractmethod
    def compute_outputs(self):
        pass

class InputImageNode (Node):
    def __init__(self):
        return super().__init__(name="Input node",
                                inputs=[],
                                outputs=[ImageOutput()])

    def add_node(self, parent):
        super().add_node(parent=parent)

    def compute_outputs(self):
        pass

class OutputImageNode (Node):
    def __init__(self):
        super().__init__(name="Output node",
                         inputs=[ImageInput()],
                         outputs=[])

    def add_node(self, parent):
        super().add_node(parent=parent)

    def compute_outputs(self):
        pass 