from abc import ABC, abstractmethod
import random
import dearpygui.dearpygui as dpg

class Output(ABC):
    def __init__(self, name):
       self.name = name
       self.tag = name + "_" + str(random.randint(0, 50000))

    @abstractmethod
    def add_output_to_node():
        pass

    def set_value(self, value):
        self.value = value

    def get_value(self):
        return self.value

    def __str__(self):
        return f"name: {self.name}, tag: {self.tag}"

class ImageOutput(Output):
    def __init__(self):
        super().__init__("Image Ouput")

    def add_output_to_node(self, parent):
        with dpg.node_attribute(tag=self.tag,
                                label=self.name,
                                parent=parent,
                                attribute_type=dpg.mvNode_Attr_Output):

            dpg.add_text("Image",
                         tag=self.name + "_TextSlot_" + str(random.randint(0, 50000)))

    def __str__(self):
        return "Image Output: " + super().__str__()
