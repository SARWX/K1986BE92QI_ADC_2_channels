#!/usr/bin/env python3
# -*- coding: utf-8 -*-

#
# SPDX-License-Identifier: GPL-3.0
#
# GNU Radio Python Flow Graph
# Title: qpsk_stage6
# Author: Barry Duggan
# GNU Radio version: 3.10.8.0

from PyQt5 import Qt
from gnuradio import qtgui
from gnuradio import blocks
from gnuradio import gr
from gnuradio.filter import firdes
from gnuradio.fft import window
import sys
import signal
from PyQt5 import Qt
from argparse import ArgumentParser
from gnuradio.eng_arg import eng_float, intx
from gnuradio import eng_notation
import qpsk_stage6_epy_block_0_0 as epy_block_0_0  # embedded python block
import qpsk_stage6_epy_block_1_0_0_0 as epy_block_1_0_0_0  # embedded python block
import qpsk_stage6_epy_block_1_0_0_1 as epy_block_1_0_0_1  # embedded python block
import sip



class qpsk_stage6(gr.top_block, Qt.QWidget):

    def __init__(self):
        gr.top_block.__init__(self, "qpsk_stage6", catch_exceptions=True)
        Qt.QWidget.__init__(self)
        self.setWindowTitle("qpsk_stage6")
        qtgui.util.check_set_qss()
        try:
            self.setWindowIcon(Qt.QIcon.fromTheme('gnuradio-grc'))
        except BaseException as exc:
            print(f"Qt GUI: Could not set Icon: {str(exc)}", file=sys.stderr)
        self.top_scroll_layout = Qt.QVBoxLayout()
        self.setLayout(self.top_scroll_layout)
        self.top_scroll = Qt.QScrollArea()
        self.top_scroll.setFrameStyle(Qt.QFrame.NoFrame)
        self.top_scroll_layout.addWidget(self.top_scroll)
        self.top_scroll.setWidgetResizable(True)
        self.top_widget = Qt.QWidget()
        self.top_scroll.setWidget(self.top_widget)
        self.top_layout = Qt.QVBoxLayout(self.top_widget)
        self.top_grid_layout = Qt.QGridLayout()
        self.top_layout.addLayout(self.top_grid_layout)

        self.settings = Qt.QSettings("GNU Radio", "qpsk_stage6")

        try:
            geometry = self.settings.value("geometry")
            if geometry:
                self.restoreGeometry(geometry)
        except BaseException as exc:
            print(f"Qt GUI: Could not restore geometry: {str(exc)}", file=sys.stderr)

        ##################################################
        # Blocks
        ##################################################

        self.qtgui_time_sink_x_0_2_1_0 = qtgui.time_sink_f(
            (1024*4), #size
            100000, #samp_rate
            "", #name
            2, #number of inputs
            None # parent
        )
        self.qtgui_time_sink_x_0_2_1_0.set_update_time(0.10)
        self.qtgui_time_sink_x_0_2_1_0.set_y_axis(0, 1)

        self.qtgui_time_sink_x_0_2_1_0.set_y_label('Amplitude', "")

        self.qtgui_time_sink_x_0_2_1_0.enable_tags(False)
        self.qtgui_time_sink_x_0_2_1_0.set_trigger_mode(qtgui.TRIG_MODE_FREE, qtgui.TRIG_SLOPE_POS, 0.0, 0, 0, "")
        self.qtgui_time_sink_x_0_2_1_0.enable_autoscale(False)
        self.qtgui_time_sink_x_0_2_1_0.enable_grid(False)
        self.qtgui_time_sink_x_0_2_1_0.enable_axis_labels(True)
        self.qtgui_time_sink_x_0_2_1_0.enable_control_panel(False)
        self.qtgui_time_sink_x_0_2_1_0.enable_stem_plot(False)


        labels = ['Signal 1', 'Signal 2', 'Signal 3', 'Signal 4', 'Signal 5',
            'Signal 6', 'Signal 7', 'Signal 8', 'Signal 9', 'Signal 10']
        widths = [1, 1, 1, 1, 1,
            1, 1, 1, 1, 1]
        colors = ['blue', 'red', 'green', 'black', 'cyan',
            'magenta', 'yellow', 'dark red', 'dark green', 'dark blue']
        alphas = [1.0, 1.0, 1.0, 1.0, 1.0,
            1.0, 1.0, 1.0, 1.0, 1.0]
        styles = [1, 1, 1, 1, 1,
            1, 1, 1, 1, 1]
        markers = [-1, -1, -1, -1, -1,
            -1, -1, -1, -1, -1]


        for i in range(2):
            if len(labels[i]) == 0:
                self.qtgui_time_sink_x_0_2_1_0.set_line_label(i, "Data {0}".format(i))
            else:
                self.qtgui_time_sink_x_0_2_1_0.set_line_label(i, labels[i])
            self.qtgui_time_sink_x_0_2_1_0.set_line_width(i, widths[i])
            self.qtgui_time_sink_x_0_2_1_0.set_line_color(i, colors[i])
            self.qtgui_time_sink_x_0_2_1_0.set_line_style(i, styles[i])
            self.qtgui_time_sink_x_0_2_1_0.set_line_marker(i, markers[i])
            self.qtgui_time_sink_x_0_2_1_0.set_line_alpha(i, alphas[i])

        self._qtgui_time_sink_x_0_2_1_0_win = sip.wrapinstance(self.qtgui_time_sink_x_0_2_1_0.qwidget(), Qt.QWidget)
        self.top_layout.addWidget(self._qtgui_time_sink_x_0_2_1_0_win)
        self.qtgui_time_sink_x_0_2_1 = qtgui.time_sink_f(
            (1024*4), #size
            100000, #samp_rate
            "", #name
            2, #number of inputs
            None # parent
        )
        self.qtgui_time_sink_x_0_2_1.set_update_time(0.10)
        self.qtgui_time_sink_x_0_2_1.set_y_axis(0, 1)

        self.qtgui_time_sink_x_0_2_1.set_y_label('Amplitude', "")

        self.qtgui_time_sink_x_0_2_1.enable_tags(False)
        self.qtgui_time_sink_x_0_2_1.set_trigger_mode(qtgui.TRIG_MODE_FREE, qtgui.TRIG_SLOPE_POS, 0.0, 0, 0, "")
        self.qtgui_time_sink_x_0_2_1.enable_autoscale(False)
        self.qtgui_time_sink_x_0_2_1.enable_grid(False)
        self.qtgui_time_sink_x_0_2_1.enable_axis_labels(True)
        self.qtgui_time_sink_x_0_2_1.enable_control_panel(False)
        self.qtgui_time_sink_x_0_2_1.enable_stem_plot(False)


        labels = ['Signal 1', 'Signal 2', 'Signal 3', 'Signal 4', 'Signal 5',
            'Signal 6', 'Signal 7', 'Signal 8', 'Signal 9', 'Signal 10']
        widths = [1, 1, 1, 1, 1,
            1, 1, 1, 1, 1]
        colors = ['blue', 'red', 'green', 'black', 'cyan',
            'magenta', 'yellow', 'dark red', 'dark green', 'dark blue']
        alphas = [1.0, 1.0, 1.0, 1.0, 1.0,
            1.0, 1.0, 1.0, 1.0, 1.0]
        styles = [1, 1, 1, 1, 1,
            1, 1, 1, 1, 1]
        markers = [-1, -1, -1, -1, -1,
            -1, -1, -1, -1, -1]


        for i in range(2):
            if len(labels[i]) == 0:
                self.qtgui_time_sink_x_0_2_1.set_line_label(i, "Data {0}".format(i))
            else:
                self.qtgui_time_sink_x_0_2_1.set_line_label(i, labels[i])
            self.qtgui_time_sink_x_0_2_1.set_line_width(i, widths[i])
            self.qtgui_time_sink_x_0_2_1.set_line_color(i, colors[i])
            self.qtgui_time_sink_x_0_2_1.set_line_style(i, styles[i])
            self.qtgui_time_sink_x_0_2_1.set_line_marker(i, markers[i])
            self.qtgui_time_sink_x_0_2_1.set_line_alpha(i, alphas[i])

        self._qtgui_time_sink_x_0_2_1_win = sip.wrapinstance(self.qtgui_time_sink_x_0_2_1.qwidget(), Qt.QWidget)
        self.top_grid_layout.addWidget(self._qtgui_time_sink_x_0_2_1_win, 1, 2, 2, 2)
        for r in range(1, 3):
            self.top_grid_layout.setRowStretch(r, 1)
        for c in range(2, 4):
            self.top_grid_layout.setColumnStretch(c, 1)
        self.qtgui_time_sink_x_0_2 = qtgui.time_sink_f(
            (1024*4), #size
            100000, #samp_rate
            "", #name
            1, #number of inputs
            None # parent
        )
        self.qtgui_time_sink_x_0_2.set_update_time(0.10)
        self.qtgui_time_sink_x_0_2.set_y_axis(0, 256)

        self.qtgui_time_sink_x_0_2.set_y_label('Amplitude', "")

        self.qtgui_time_sink_x_0_2.enable_tags(True)
        self.qtgui_time_sink_x_0_2.set_trigger_mode(qtgui.TRIG_MODE_FREE, qtgui.TRIG_SLOPE_POS, 0.0, 0, 0, "")
        self.qtgui_time_sink_x_0_2.enable_autoscale(False)
        self.qtgui_time_sink_x_0_2.enable_grid(False)
        self.qtgui_time_sink_x_0_2.enable_axis_labels(True)
        self.qtgui_time_sink_x_0_2.enable_control_panel(False)
        self.qtgui_time_sink_x_0_2.enable_stem_plot(False)


        labels = ['Signal 1', 'Signal 2', 'Signal 3', 'Signal 4', 'Signal 5',
            'Signal 6', 'Signal 7', 'Signal 8', 'Signal 9', 'Signal 10']
        widths = [1, 1, 1, 1, 1,
            1, 1, 1, 1, 1]
        colors = ['blue', 'red', 'green', 'black', 'cyan',
            'magenta', 'yellow', 'dark red', 'dark green', 'dark blue']
        alphas = [1.0, 1.0, 1.0, 1.0, 1.0,
            1.0, 1.0, 1.0, 1.0, 1.0]
        styles = [1, 1, 1, 1, 1,
            1, 1, 1, 1, 1]
        markers = [-1, -1, -1, -1, -1,
            -1, -1, -1, -1, -1]


        for i in range(1):
            if len(labels[i]) == 0:
                self.qtgui_time_sink_x_0_2.set_line_label(i, "Data {0}".format(i))
            else:
                self.qtgui_time_sink_x_0_2.set_line_label(i, labels[i])
            self.qtgui_time_sink_x_0_2.set_line_width(i, widths[i])
            self.qtgui_time_sink_x_0_2.set_line_color(i, colors[i])
            self.qtgui_time_sink_x_0_2.set_line_style(i, styles[i])
            self.qtgui_time_sink_x_0_2.set_line_marker(i, markers[i])
            self.qtgui_time_sink_x_0_2.set_line_alpha(i, alphas[i])

        self._qtgui_time_sink_x_0_2_win = sip.wrapinstance(self.qtgui_time_sink_x_0_2.qwidget(), Qt.QWidget)
        self.top_grid_layout.addWidget(self._qtgui_time_sink_x_0_2_win, 0, 0, 1, 4)
        for r in range(0, 1):
            self.top_grid_layout.setRowStretch(r, 1)
        for c in range(0, 4):
            self.top_grid_layout.setColumnStretch(c, 1)
        self.qtgui_const_sink_x_0 = qtgui.const_sink_c(
            10000, #size
            "", #name
            1, #number of inputs
            None # parent
        )
        self.qtgui_const_sink_x_0.set_update_time(0.10)
        self.qtgui_const_sink_x_0.set_y_axis((-0.5), 1.5)
        self.qtgui_const_sink_x_0.set_x_axis((-0.5), 1.5)
        self.qtgui_const_sink_x_0.set_trigger_mode(qtgui.TRIG_MODE_FREE, qtgui.TRIG_SLOPE_POS, 0.0, 0, "")
        self.qtgui_const_sink_x_0.enable_autoscale(False)
        self.qtgui_const_sink_x_0.enable_grid(False)
        self.qtgui_const_sink_x_0.enable_axis_labels(True)


        labels = ['', '', '', '', '',
            '', '', '', '', '']
        widths = [1, 1, 1, 1, 1,
            1, 1, 1, 1, 1]
        colors = ["blue", "red", "green", "black", "cyan",
            "magenta", "yellow", "dark red", "dark green", "dark blue"]
        styles = [0, 0, 0, 0, 0,
            0, 0, 0, 0, 0]
        markers = [0, 0, 0, 0, 0,
            0, 0, 0, 0, 0]
        alphas = [1.0, 1.0, 1.0, 1.0, 1.0,
            1.0, 1.0, 1.0, 1.0, 1.0]

        for i in range(1):
            if len(labels[i]) == 0:
                self.qtgui_const_sink_x_0.set_line_label(i, "Data {0}".format(i))
            else:
                self.qtgui_const_sink_x_0.set_line_label(i, labels[i])
            self.qtgui_const_sink_x_0.set_line_width(i, widths[i])
            self.qtgui_const_sink_x_0.set_line_color(i, colors[i])
            self.qtgui_const_sink_x_0.set_line_style(i, styles[i])
            self.qtgui_const_sink_x_0.set_line_marker(i, markers[i])
            self.qtgui_const_sink_x_0.set_line_alpha(i, alphas[i])

        self._qtgui_const_sink_x_0_win = sip.wrapinstance(self.qtgui_const_sink_x_0.qwidget(), Qt.QWidget)
        self.top_grid_layout.addWidget(self._qtgui_const_sink_x_0_win, 1, 0, 2, 2)
        for r in range(1, 3):
            self.top_grid_layout.setRowStretch(r, 1)
        for c in range(0, 2):
            self.top_grid_layout.setColumnStretch(c, 1)
        self.epy_block_1_0_0_1 = epy_block_1_0_0_1.blk(example_param=1.0)
        self.epy_block_1_0_0_0 = epy_block_1_0_0_0.blk(mode=1)
        self.epy_block_0_0 = epy_block_0_0.ADIBlock(portNumber=10, mode=3)
        self.blocks_null_source_0_0 = blocks.null_source(gr.sizeof_float*1)
        self.blocks_null_source_0 = blocks.null_source(gr.sizeof_float*1)
        self.blocks_float_to_complex_0 = blocks.float_to_complex(1)


        ##################################################
        # Connections
        ##################################################
        self.connect((self.blocks_float_to_complex_0, 0), (self.qtgui_const_sink_x_0, 0))
        self.connect((self.blocks_null_source_0, 0), (self.epy_block_0_0, 0))
        self.connect((self.blocks_null_source_0_0, 0), (self.epy_block_0_0, 1))
        self.connect((self.epy_block_0_0, 0), (self.epy_block_1_0_0_1, 0))
        self.connect((self.epy_block_0_0, 1), (self.epy_block_1_0_0_1, 1))
        self.connect((self.epy_block_0_0, 0), (self.qtgui_time_sink_x_0_2_1_0, 0))
        self.connect((self.epy_block_0_0, 1), (self.qtgui_time_sink_x_0_2_1_0, 1))
        self.connect((self.epy_block_1_0_0_0, 0), (self.qtgui_time_sink_x_0_2, 0))
        self.connect((self.epy_block_1_0_0_1, 0), (self.blocks_float_to_complex_0, 0))
        self.connect((self.epy_block_1_0_0_1, 1), (self.blocks_float_to_complex_0, 1))
        self.connect((self.epy_block_1_0_0_1, 0), (self.epy_block_1_0_0_0, 0))
        self.connect((self.epy_block_1_0_0_1, 1), (self.epy_block_1_0_0_0, 1))
        self.connect((self.epy_block_1_0_0_1, 0), (self.qtgui_time_sink_x_0_2_1, 0))
        self.connect((self.epy_block_1_0_0_1, 1), (self.qtgui_time_sink_x_0_2_1, 1))


    def closeEvent(self, event):
        self.settings = Qt.QSettings("GNU Radio", "qpsk_stage6")
        self.settings.setValue("geometry", self.saveGeometry())
        self.stop()
        self.wait()

        event.accept()




def main(top_block_cls=qpsk_stage6, options=None):

    qapp = Qt.QApplication(sys.argv)

    tb = top_block_cls()

    tb.start()

    tb.show()

    def sig_handler(sig=None, frame=None):
        tb.stop()
        tb.wait()

        Qt.QApplication.quit()

    signal.signal(signal.SIGINT, sig_handler)
    signal.signal(signal.SIGTERM, sig_handler)

    timer = Qt.QTimer()
    timer.start(500)
    timer.timeout.connect(lambda: None)

    qapp.exec_()

if __name__ == '__main__':
    main()
