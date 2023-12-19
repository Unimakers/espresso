import dearpygui.dearpygui as dpg

TABLE_WIDTH = 3000
TABLE_HEIGHT = 2000
TABLE_RATIO = 0.3
TABLE_VIEW_WIDTH = (int)(TABLE_WIDTH * TABLE_RATIO)
TABLE_VIEW_HEIGHT = (int)(TABLE_HEIGHT * TABLE_RATIO)
TABLE_REAL_RATIO = TABLE_WIDTH / TABLE_VIEW_WIDTH
MARGIN_OFFSET = 30
robot_pos = [0, 0]
robot_size = [450 * TABLE_RATIO, 450 * TABLE_RATIO]


class Table2D:
    def register(self):
        width, height, _, data = dpg.load_image("assets/table.png")
        with dpg.texture_registry(show=False):
            dpg.add_static_texture(
                width=width,
                height=height,
                default_value=data,
                tag="table_texture",
            )
        with dpg.window(
            label="Table 2D",
            tag="table",
            pos=[205, 0],
            height=640,
            no_close=True,
            no_move=True,
            no_resize=True,
            no_collapse=True,
        ):
            dpg.add_image(
                "table_texture",
                width=TABLE_VIEW_WIDTH,
                height=TABLE_VIEW_HEIGHT,
                tag="table_img",
            )
