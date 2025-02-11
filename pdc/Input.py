from abc import ABC, abstractmethod
import random
import dearpygui.dearpygui as dpg

class Input(ABC):
    def __init__(self, name):
       self.name = name
       self.tag = name + "_" + str(random.randint(0, 50000))

    @abstractmethod
    def add_input_to_node(self, parent):
        pass

    def set_value(self, value):
        self.value = value

    def get_value(self):
        return self.value

    def __str__(self):
        return f"name: {self.name}, tag: {self.tag}"

class ImageInput(Input):
    def __init__(self):
        super().__init__("Image Input")

    def add_input_to_node(self, parent):
        with dpg.node_attribute(tag=self.tag,
                                label=self.name,
                                parent=parent,
                                attribute_type=dpg.mvNode_Attr_Input):

            dpg.add_text("Image",
                         tag=self.name + "_TextSlot_" + str(random.randint(0, 50000)))

    def __str__(self):
        return "Image Input: " + super().__str__()