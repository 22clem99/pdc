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
        self.inputs = {}
        for input in inputs:
            self.inputs[input.tag] = input
        # Create dict with all outputs
        self.outputs = {}
        for output in outputs:
            self.outputs[output.tag] = output

        logger.debug(f"Add new node [Name]: {self.name}, [Tag]: {self.tag}, [Inputs]: {self.inputs}, [Outputs]: {self.outputs}")

    def add_node(self, parent):
        with dpg.node(tag=self.tag, label=self.name, parent=parent):
            for input in self.inputs.values():
                input.add_input_to_node(parent=self.tag)
            for output in self.outputs.values():
                output.add_output_to_node(parent=self.tag)


    @abstractmethod
    def compute_outputs(self):
        pass

class InputImageNode (Node):
    def __init__(self):
        return super().__init__(name="Input node",
                                inputs=[ImageInput()],
                                outputs=[])

    def add_node(self, parent):
        super().add_node(parent=parent)

    def compute_outputs(self):
        pass

class OutputImageNode (Node):
    def __init__(self):
        super().__init__(name="Output node",
                         inputs=[],
                         outputs=[ImageOutput()])

    def add_node(self, parent):
        super().add_node(parent=parent)

    def compute_outputs(self):
        pass 