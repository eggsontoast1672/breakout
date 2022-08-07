use crate::block::{Block, BLOCK_HEIGHT, BLOCK_WIDTH};
use macroquad::prelude::*;

pub const BOARD_WIDTH: u32 = 5;
pub const BOARD_HEIGHT: u32 = 5;
pub const PADDING: f32 = 5.0;

pub struct Board {
    blocks: Vec<Block>,
}

impl Board {
    pub fn new() -> Self {
        let start_position = Vec2::new(
            (screen_width() - BOARD_WIDTH as f32 * BLOCK_WIDTH) / 2.0,
            80.0,
        );

        Self {
            blocks: (0..BOARD_WIDTH * BOARD_HEIGHT)
                .map(|i| {
                    Block::new(
                        (BLOCK_WIDTH + PADDING) * ((i % 5) as f32) + start_position.x,
                        (BLOCK_HEIGHT + PADDING) * ((i / 5) as f32) + start_position.y,
                    )
                })
                .collect(),
        }
    }

    pub fn draw(&self) {
        self.blocks.iter().for_each(|block| block.draw());
    }
}
