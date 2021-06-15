using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace _2048
{
    enum Direction
    {
        up=0,down,left,right
    }
    struct Location
    {
        public Location(int x,int y):this()
        {
            this.X = x;
            this.Y = y;
        }
        private int x;
        private int y;
        public int X
        {
            get { return this.x; }
            set { this.x = value; }
        }
        public int Y
        {
            get { return this.y; }
            set { this.y = value; }
        }
    }
    class GameCore
    {
        private List<Location> lList;
        private Random random;
        private int[,] map;
        public int[,] Map
        {
            get{ return this.map; }
         }

        private int[] mergeArr;
        private int[] removeZeroArr;
        public GameCore()
        {
            lList = new List<Location>(16);
            random = new Random();
            map = new int[4, 4];
            mergeArr = new int[4];
            removeZeroArr = new int[4];
        }
        private void removeZero()
        {
            int index = 0;
            Array.Clear(removeZeroArr, 0, 4);
            for (int i = 0; i < 4; i++)
            {
                if (mergeArr[i] != 0)
                {
                    removeZeroArr[index++] = mergeArr[i];
                }
            }
            removeZeroArr.CopyTo(mergeArr, 0);
        }
        private void merge()
        {
            removeZero();
            for (int i = 0; i < 3; i++)
            {
                if (mergeArr[i] != 0 && mergeArr[i] == mergeArr[i + 1])
                {
                    mergeArr[i] += mergeArr[i + 1];
                    mergeArr[i + 1] = 0;
                }
            }
            removeZero();
        }
        private void moveLeft()
        {
            for (int j = 0; j < 4; j++)
            {
                for (int i = 0; i < 4; i++)
                {
                    mergeArr[i] = map[j,i];
                }
                merge();
                for (int i = 0; i < 4; i++)
                {
                    map[j, i] = mergeArr[i];
                }
            }

        }
        private void moveRight()
        {
            for (int j = 0; j < 4; j++)
            {
                for (int i = 0; i < 4; i++)
                {
                    mergeArr[i] = map[j, 3-i];
                }
                merge();
                for (int i = 0; i < 4; i++)
                {
                    map[j, 3-i] = mergeArr[i];
                }
            }
        }
        private void moveUp()
        {
            for (int j = 0; j < 4; j++)
            {
                for (int i = 0; i < 4; i++)
                {
                    mergeArr[i] = map[i, j];
                }
                merge();
                for (int i = 0; i < 4; i++)
                {
                    map[i, j] = mergeArr[i];
                }
            }
        }
        private void moveDown()
        {
            for (int j = 0; j < 4; j++)
            {
                for (int i = 0; i < 4; i++)
                {
                    mergeArr[i] = map[3-i, j];
                }
                merge();
                for (int i = 0; i < 4; i++)
                {
                    map[3-i, j] = mergeArr[i];
                }
            }
        }
        private void calculateEmpty()
        {
            lList.Clear();
            for (int i = 0; i < 4; i++)
            {
                for (int j = 0; j < 4; j++)
                {
                    if (map[i,j] == 0)
                    {
                        Location l = new Location(j, i);
                        lList.Add(l);
                    }
                }
            }
        }
        public void generateNumber()
        {
            calculateEmpty();
            if (lList.Count > 0)
            {
                int randomNumber = random.Next(0, lList.Count);
                Location l = lList[randomNumber];
                map[l.Y, l.X] = random.Next(0, 10) == 1 ? 4 : 2;
            }
        }
        public void move(Direction direction)
        {
            switch (direction)
            {
                case Direction.up:
                    this.moveUp();
                    break;
                case Direction.down:
                    this.moveDown();
                    break;
                case Direction.left:
                    this.moveLeft();
                    break;
                case Direction.right:
                    this.moveRight();
                    break;
            }
        }
    }
}
