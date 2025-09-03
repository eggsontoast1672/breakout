using Microsoft.Xna.Framework;
using Microsoft.Xna.Framework.Graphics;
using Microsoft.Xna.Framework.Input;

namespace Breakout;

public class Game1 : Game
{
    private GraphicsDeviceManager _graphics;
    private SpriteBatch _spriteBatch;

    private Texture2D _awesomeFace;

    public Game1()
    {
        _graphics = new GraphicsDeviceManager(this);
        Content.RootDirectory = "Content";
        IsMouseVisible = true;
    }

    protected override void Initialize()
    {
        _graphics.PreferredBackBufferWidth = 800;
        _graphics.PreferredBackBufferHeight = 600;

        _graphics.ApplyChanges();

        base.Initialize();
    }

    protected override void LoadContent()
    {
        _spriteBatch = new SpriteBatch(GraphicsDevice);
        _awesomeFace = Content.Load<Texture2D>("awesomeface");
    }

    protected override void Update(GameTime gameTime)
    {
        if (GamePad.GetState(PlayerIndex.One).Buttons.Back == ButtonState.Pressed || Keyboard.GetState().IsKeyDown(Keys.Escape))
            Exit();

        // TODO: Add your update logic here

        base.Update(gameTime);
    }

    protected override void Draw(GameTime gameTime)
    {
        GraphicsDevice.Clear(Color.Black);

        var rect = new Rectangle(200 + (int)(_awesomeFace.Width / 2.0f), 200 + (int)(_awesomeFace.Height / 2.0f), 300, 400);
        var color = new Color(0.0f, 1.0f, 0.0f);
        var rotation = float.DegreesToRadians(45);
        var origin = new Vector2(_awesomeFace.Width / 2.0f, _awesomeFace.Height / 2.0f);
        var effects = new SpriteEffects();

        _spriteBatch.Begin();
        _spriteBatch.Draw(_awesomeFace, rect, null, color, rotation, origin, effects, 0.0f);
        _spriteBatch.End();

        base.Draw(gameTime);
    }
}
