using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace _2048
{
    class Program
    {
        static void Main(string[] args)
        {
            GameCore game = new GameCore();
            game.generateNumber();
            game.generateNumber();
            showMap(game.Map);
            while (true)
            {
                key(game);
                game.generateNumber();
                showMap(game.Map);
            }
            
        }
        private static void showMap(int[,] map)
        {
            Console.Clear();
            for (int i = 0; i < 4; i++)
            {
                for (int j = 0; j < 4; j++)
                {
                    Console.Write(map[i, j]);
                    Console.Write(" ");
                }
                Console.Write("\n");
            }
        }
        private static void key(GameCore game)
        {
            string c = Console.ReadLine();
            switch (c)
            {
                case "w":
                    game.move(Direction.up);
                    break;
                case "s":
                    game.move(Direction.down);
                    break;
                case "a":
                    game.move(Direction.left);
                    break;
                case "d":
                    game.move(Direction.right);
                    break;
            }
        }
    }
}
