using System.Collections.Generic;
using System.IO;
using System.Linq;

using Microsoft.Xna.Framework.Graphics;

namespace Breakout;

class Level
{
    private List<GameObject> _bricks;

    public void Load(string file, uint levelWidth, uint levelHeight)
    {
        var tileData = new List<List<uint>>();

        _bricks.Clear();

        using (StreamReader reader = File.OpenText(file))
        {
            string line;
            while ((line = reader.ReadLine()) is not null)
            {
                var row = line.Split(' ').Select(uint.Parse).ToList();
                tileData.Add(row);
            }
        }

        Init(tileData, levelWidth, levelHeight);
    }

    public void Draw(SpriteBatch spriteBatch)
    {
        foreach (GameObject tile in _bricks)
        {
            if (!tile.Destroyed)
            {
                tile.Draw(spriteBatch);
            }
        }
    }

    public bool IsCompleted() => _bricks.Where(b => !b.IsSolid).All(b => b.Destroyed);

    private void Init(List<List<uint>> tileData, uint levelWidth, uint levelHeight) { }
}
