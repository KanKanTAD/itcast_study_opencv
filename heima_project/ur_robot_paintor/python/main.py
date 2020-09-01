#!/usr/bin/env python

import PyQt5
import sys

from PyQt5.QtWidgets import QApplication, QWidget
# from PyQt5.QtGui import QWidget

if __name__ == '__main__':

    a = QApplication(sys.argv)

    wnd = QWidget()
    wnd.show()

    sys.exit(a.exec())
