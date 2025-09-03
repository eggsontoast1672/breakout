using Microsoft.Xna.Framework;
using Microsoft.Xna.Framework.Graphics;

namespace Breakout;

class GameObject
{
    public Vector2 Position = Vector2.Zero;
    public Vector2 Size = Vector2.One;
    public Vector2 Velocity = Vector2.Zero;
    public Color Color = Color.White;
    public float Rotation = 0.0f;
    public bool IsSolid = false;
    public bool Destroyed = false;
    public Texture2D Sprite;

    public GameObject(Vector2 position, Vector2 size, Texture2D sprite)
    {
        Position = position;
        Size = size;
        Sprite = sprite;
    }

    public void Draw(SpriteBatch spriteBatch)
    {
        spriteBatch.Draw(Sprite, Position, Color);
    }
}
