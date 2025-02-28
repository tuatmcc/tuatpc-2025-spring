import logging
import sys

def setup_logger():
    """
    ロギングの設定を行う関数
    """
    # ルートロガーを取得
    logger = logging.getLogger()
    logger.setLevel(logging.INFO)  # ログレベルをINFOに設定
    
    # すでにハンドラが設定されている場合は削除
    if logger.handlers:
        logger.handlers = []
    
    # コンソールに出力するハンドラ
    console_handler = logging.StreamHandler(sys.stdout)
    console_handler.setLevel(logging.INFO)
    
    # フォーマットの設定
    formatter = logging.Formatter('[%(levelname)s] %(asctime)s - %(message)s')
    console_handler.setFormatter(formatter)
    
    # ハンドラをロガーに追加
    logger.addHandler(console_handler)
    
    return logger

# ロガーのセットアップ
logger = setup_logger()
