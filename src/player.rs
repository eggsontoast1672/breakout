// Note that the width and height of the player aren't being stored inside the
// player stuct itself. I decided to do this because the width and height of the
// player will never be modified, so to improve readability I just used public
// constants. This works well since there will only ever be on player in the
// game anyway.

use macroquad::prelude::*;

pub const PLAYER_WIDTH: f32 = 150.0;
pub const PLAYER_HEIGHT: f32 = 40.0;
pub const PLAYER_SPEED: f32 = 200.0;

pub struct Player {
    pub position: Vec2,
}

impl Player {
    pub fn update(&mut self, dt: f32) {
        let offset = match (is_key_down(KeyCode::A), is_key_down(KeyCode::D)) {
            (true, false) => -1.0,
            (false, true) => 1.0,
            _ => 0.0,
        };

        self.position.x += PLAYER_SPEED * dt * offset;
    }

    pub fn draw(&self) {
        draw_rectangle(
            self.position.x,
            self.position.y,
            PLAYER_WIDTH,
            PLAYER_HEIGHT,
            BLUE,
        );
    }
}
