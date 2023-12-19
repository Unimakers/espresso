import dearpygui.dearpygui as dpg


class LeftPane:
    height: int | None
    width: int

    def __init__(self):
        self.height = dpg.get_item_height("table")
        if self.height is None:
            self.height = 720

    def register(self):
        with dpg.texture_registry(show=False):
            width, height, _, data = dpg.load_image("assets/logo.png")
            dpg.add_static_texture(
                width=width,
                height=height,
                default_value=data,
                tag="logo_texture",
            )
        with dpg.window(
            label="RoboVision 0.0.1",
            no_close=True,
            pos=[0, 0],
            width=200,
            height=self.height,
            no_collapse=True,
            no_move=True,
        ):
            dpg.add_image(
                "logo_texture",
                width=185,
                height=32,
                tag="logo_img",
            )
            dpg.add_text(source="mouse_pos")
