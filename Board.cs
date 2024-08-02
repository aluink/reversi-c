using System;
namespace Reversi {

  public class Masks {
    public static void GenerateNeighborMasks() {
      for (int pos = 0;pos < 64;pos++) {
        ulong mask = 0;
        var LEFT = pos % 8 > 0;
        var RIGHT = pos % 8 < 7;
        var UP = pos < 56;
        var DOWN = pos > 7;

        if (DOWN) { // DOWN
          mask |= 1UL << pos - 8;

          // DOWN-LEFT
          if (LEFT) mask |= 1UL << pos - 9;

          // DOWN-RIGHT
          if (RIGHT) mask |= 1UL << pos - 7;
        }

        if (UP) { // UP
          mask |= 1UL << pos + 8;

          // UP-LEFT
          if (LEFT) mask |= 1UL << pos + 7;

          // UP-RIGHT
          if (RIGHT) mask |= 1UL << pos + 9;
        }

        // LEFT
        if (LEFT) mask |= 1UL << pos - 1;

        // RIGHT
        if (RIGHT) mask |= 1UL << pos + 1;
        Console.WriteLine(PosToCoords(pos));
        PrintBitboard(mask);
      }
    }

    public static string PosToCoords(int pos) {
      var col = pos % 8;
      var row = pos / 8 + 1;
      // return (char)(1 + 'A');
      return $"{(char)(col % 8 + 'A')}{row}";
    }

    public static void PrintBitboard(ulong board) {
      for (int row = 7;row >= 0;row--) {
        for (int col = 0;col < 8;col++) {
          Console.Write(board >> (row*8+col) & 1);
        }
        Console.WriteLine();
      }
      Console.WriteLine();
    }

    //public ulong[] NEIGHTBOR_MASKS = new ulong[64] {
    //  0x40C0000000000000UL,
    //};

    public static void PrintMask(ulong mask) {
      for (var row = 8;row >= 0;row--) {
        for (var col = 0;col < 8; col++) {
          Console.Write(mask >> row * 8 + col & 1);
        }
        Console.WriteLine();
      }
    }
  }

  public enum Piece {
    Black = 0,
    White = 1
  }

  public class Board {
    ulong[] bitboards = new ulong[2];
    short turn;
    public Board() {

    }

    public static Board NewGame() {
      return new Board {
        turn = 0,
        bitboards = new[] {
          0x0000001008000000UL,
          0x0000000810000000UL
        }
      };
    }




    public void GetLegalMoves() {
      var currentPlayerBoard = bitboards[turn];
      var otherPlayerBoard = bitboards[turn ^ 1];

      var tmp = currentPlayerBoard;
      while (tmp > 0) {
        
      }
    }

    public Piece? GetPos(int col, int row) => GetPos(row * 8 + col);

    public Piece? GetPos(int pos) {
      if ((bitboards[0] >> pos & 1UL) > 0) return Piece.Black;
      if ((bitboards[1] >> pos & 1UL) > 0) return Piece.White;
      return null;
    }

    public void Print() {
      Console.WriteLine("   +---+---+---+---+---+---+---+---+");
      for (var row = 7;row >= 0;row--) {
        Console.Write("   ");
        for (var col = 0;col < 8;col++) {
          var piece = GetPos(col, row);
          char c = piece == Piece.White
            ? 'X'
            : piece == Piece.Black
              ? 'O'
              : ' ';
          Console.Write($"+ {c} ");
        }
        Console.WriteLine("+");
        Console.WriteLine($" {row+1} +---+---+---+---+---+---+---+---+");
      }
      Console.WriteLine("     A   B   C   D   E   F   G   H");
    }

    public void Makemove(int col, int row) => Makemove(row * 8 + col);

    public void Makemove(int pos) {
      bitboards[turn] |= 1UL << pos;
      turn ^= 1;
    }
  }
}
