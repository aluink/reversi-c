using System;

namespace Reversi {
  class Program {
    static void Main(string[] args) {
      // Board b = Board.NewGame();
      // b.Print();

      //0x0000001008000000UL,
      //0x0000000810000000UL

      Masks.GenerateNeighborMasks();
    }
  }
}
