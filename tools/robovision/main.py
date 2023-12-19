from math import floor
import dearpygui.dearpygui as dpg
from components.table import Table2D
from components.leftpane import LeftPane


TABLE_WIDTH = 3000
TABLE_HEIGHT = 2000
TABLE_RATIO = 0.3
TABLE_VIEW_WIDTH = (int)(TABLE_WIDTH * TABLE_RATIO)
TABLE_VIEW_HEIGHT = (int)(TABLE_HEIGHT * TABLE_RATIO)
TABLE_REAL_RATIO = TABLE_WIDTH / TABLE_VIEW_WIDTH
MARGIN_OFFSET = 30
robot_pos = [0, 0]
robot_size = [450 * TABLE_RATIO, 450 * TABLE_RATIO]


def main():
    dpg.create_context()
    dpg.create_viewport(title="RoboVision")
    dpg.setup_dearpygui()
    dpg.set_viewport_vsync(True)
    dpg.toggle_viewport_fullscreen()
    register_values()
    register_handlers()

    table = Table2D()
    table.register()
    leftpane = LeftPane()
    leftpane.register()

    dpg.show_viewport()

    dpg.start_dearpygui()
    dpg.destroy_context()


def handle_mouse_click(sender, data):
    if dpg.is_item_hovered("table") and dpg.is_item_focused("table"):
        pos = dpg.get_mouse_pos()
        x = floor(pos[0] * TABLE_REAL_RATIO) - MARGIN_OFFSET
        y = floor(pos[1] * TABLE_REAL_RATIO) - MARGIN_OFFSET
        dpg.set_value("mouse_pos", f"MOUSE:{pos}")


def register_handlers():
    with dpg.handler_registry():
        dpg.add_mouse_move_handler(callback=handle_mouse_click)


def register_values():
    with dpg.value_registry():
        dpg.add_string_value(tag="mouse_pos", default_value="MOUSE:[0.0,0.0]")


if __name__ == "__main__":
    main()
