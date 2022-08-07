use breakout::board::Board;
use breakout::player::{Player, PLAYER_WIDTH};
use macroquad::prelude::*;

fn window_config() -> Conf {
    Conf {
        window_title: "Breakout".to_owned(),
        window_width: 960,
        window_height: 720,
        ..Default::default()
    }
}

#[macroquad::main(window_config)]
async fn main() {
    let mut player = Player {
        position: Vec2::new(
            screen_width() / 2.0 - PLAYER_WIDTH / 2.0,
            screen_height() - 80.0,
        ),
    };

    let board = Board::new();

    loop {
        // Update
        let dt = get_frame_time();
        player.update(dt);

        // Draw
        clear_background(WHITE);
        player.draw();
        board.draw();
        next_frame().await;
    }
}
