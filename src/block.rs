use macroquad::prelude::*;

pub const BLOCK_WIDTH: f32 = 150.0;
pub const BLOCK_HEIGHT: f32 = 40.0;

pub struct Block {
    position: Vec2,
    level: u32,
}

impl Block {
    pub fn new(x: f32, y: f32) -> Self {
        Self {
            position: Vec2::new(x, y),
            level: 3,
        }
    }

    pub fn update(&mut self, _dt: f32) {
        todo!()
    }

    pub fn draw(&self) {
        let color = match self.level {
            3 => GRAY,
            2 => YELLOW,
            1 => RED,

            // Debug state, should never happen. This is due to the fact that
            // whenever self.level reaches 0, the block will be deleted from the
            // scene and will thereby be unable to be seen. I chose the color
            // purple because why not.
            _ => PURPLE,
        };

        draw_rectangle(
            self.position.x,
            self.position.y,
            BLOCK_WIDTH,
            BLOCK_HEIGHT,
            color,
        );
    }

    pub fn decrement_level(&mut self) {
        self.level -= 1;
    }
}
