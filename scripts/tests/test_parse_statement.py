import sys
import os
import unittest
sys.path.append("scripts")

from lib.parser import parse_statement

class TestParseStatement(unittest.TestCase):
    def setUp(self):
        with open('scripts/tests/valid.md') as f:
            self.valid = f.read()
        with open('scripts/tests/valid_added_heading.md') as f:
            self.valid_added_heading = f.read()

    def test_parse_valid_statement(self):
        """
        規則に従った問題文のパーステスト
        """
        statement = parse_statement(self.valid)
        self.assertEqual(statement.name, "628")
        self.assertEqual(statement.statement, "正の整数 $A, B$ が与えられます。\n\n$A^4 + B^2 - 1$ を求めてください。")
        self.assertTrue(statement.constraints.startswith("- $1 \\leq A, B \\leq 100$"))
        self.assertEqual(statement.partial_scores, "この問題に部分点は存在しません。")
        self.assertTrue(statement.input_format.startswith("入力は以下の形式で標準入力から与えられます。"))
        self.assertEqual(statement.output_format, "答えを標準出力に出力してください。")

    def test_parse_valid_added_heading_statement(self):
        """
        必ずしも必要ではない見出しが存在する、規則に従った問題文のパーステスト
        """
        statement = parse_statement(self.valid_added_heading)
        self.assertEqual(statement.name, "628")
        self.assertTrue(statement.statement.startswith("正の整数 $A, B$ が与えられます。"))
        self.assertTrue(statement.statement.endswith("これはテスト用の見出しです。"))
        self.assertTrue(statement.constraints.startswith("- $1 \\leq A, B \\leq 100$"))
        self.assertTrue(statement.constraints.endswith("これはテスト用の見出しです。"))
        self.assertEqual(statement.partial_scores, "この問題に部分点は存在しません。")
        self.assertTrue(statement.input_format.startswith("入力は以下の形式で標準入力から与えられます。"))
        self.assertTrue(statement.input_format.endswith("これはテスト用の見出しです。"))
        self.assertEqual(statement.output_format, "答えを標準出力に出力してください。")


    def test_error_handling(self):
        """エラー処理のテスト"""
        # 不正なマークダウン
        invalid_md = "# タイトルだけ\n\n内容がない"
        with self.assertRaises(ValueError):
            parse_statement(invalid_md)

if __name__ == '__main__':
    unittest.main()
