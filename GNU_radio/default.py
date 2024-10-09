#!/usr/bin/env python3
# -*- coding: utf-8 -*-

#
# SPDX-License-Identifier: GPL-3.0
#
# GNU Radio Python Flow Graph
# Title: Not titled yet
# Author: PC_88
# GNU Radio version: 3.10.8.0

from PyQt5 import Qt
from gnuradio import qtgui
from gnuradio import analog
from gnuradio import blocks
from gnuradio import eng_notation
from gnuradio import gr
from gnuradio.filter import firdes
from gnuradio.fft import window
import sys
import signal
from PyQt5 import Qt
from argparse import ArgumentParser
from gnuradio.eng_arg import eng_float, intx
from gnuradio.qtgui import Range, RangeWidget
from PyQt5 import QtCore
import default_epy_block_0 as epy_block_0  # embedded python block
import default_epy_block_0_0_1 as epy_block_0_0_1  # embedded python block
import default_epy_block_1_0 as epy_block_1_0  # embedded python block
import sip



class default(gr.top_block, Qt.QWidget):

    def __init__(self):
        gr.top_block.__init__(self, "Not titled yet", catch_exceptions=True)
        Qt.QWidget.__init__(self)
        self.setWindowTitle("Not titled yet")
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

        self.settings = Qt.QSettings("GNU Radio", "default")

        try:
            geometry = self.settings.value("geometry")
            if geometry:
                self.restoreGeometry(geometry)
        except BaseException as exc:
            print(f"Qt GUI: Could not restore geometry: {str(exc)}", file=sys.stderr)

        ##################################################
        # Variables
        ##################################################
        self.frequency = frequency = 0
        self.DAC_sample_rate = DAC_sample_rate = 1000000
        self.samp_rate = samp_rate = 1000000
        self.generate_signal = generate_signal = 0
        self.DAC_frequency = DAC_frequency = ((int)(DAC_sample_rate /(500 -  frequency)))

        ##################################################
        # Blocks
        ##################################################

        self._samp_rate_range = Range(0, 10000000, 1, 1000000, 200)
        self._samp_rate_win = RangeWidget(self._samp_rate_range, self.set_samp_rate, "'samp_rate'", "counter_slider", int, QtCore.Qt.Horizontal)
        self.top_layout.addWidget(self._samp_rate_win)
        _generate_signal_push_button = Qt.QPushButton('Triangle')
        _generate_signal_push_button = Qt.QPushButton('Triangle')
        self._generate_signal_choices = {'Pressed': 1, 'Released': 0}
        _generate_signal_push_button.pressed.connect(lambda: self.set_generate_signal(self._generate_signal_choices['Pressed']))
        _generate_signal_push_button.released.connect(lambda: self.set_generate_signal(self._generate_signal_choices['Released']))
        self.top_layout.addWidget(_generate_signal_push_button)
        self._DAC_frequency_tool_bar = Qt.QToolBar(self)

        if None:
            self._DAC_frequency_formatter = None
        else:
            self._DAC_frequency_formatter = lambda x: str(x)

        self._DAC_frequency_tool_bar.addWidget(Qt.QLabel("DAC frequency"))
        self._DAC_frequency_label = Qt.QLabel(str(self._DAC_frequency_formatter(self.DAC_frequency)))
        self._DAC_frequency_tool_bar.addWidget(self._DAC_frequency_label)
        self.top_layout.addWidget(self._DAC_frequency_tool_bar)
        self.qtgui_time_sink_x_0_0_0 = qtgui.time_sink_f(
            10000, #size
            500000, #samp_rate
            '', #name
            2, #number of inputs
            None # parent
        )
        self.qtgui_time_sink_x_0_0_0.set_update_time(0.01)
        self.qtgui_time_sink_x_0_0_0.set_y_axis(-1, 300)

        self.qtgui_time_sink_x_0_0_0.set_y_label('Amplitude', "")

        self.qtgui_time_sink_x_0_0_0.enable_tags(False)
        self.qtgui_time_sink_x_0_0_0.set_trigger_mode(qtgui.TRIG_MODE_FREE, qtgui.TRIG_SLOPE_POS, 0.0, 0, 0, "")
        self.qtgui_time_sink_x_0_0_0.enable_autoscale(False)
        self.qtgui_time_sink_x_0_0_0.enable_grid(False)
        self.qtgui_time_sink_x_0_0_0.enable_axis_labels(True)
        self.qtgui_time_sink_x_0_0_0.enable_control_panel(True)
        self.qtgui_time_sink_x_0_0_0.enable_stem_plot(False)


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
        markers = [-1, -1, 1, -1, -1,
            -1, -1, -1, -1, -1]


        for i in range(2):
            if len(labels[i]) == 0:
                self.qtgui_time_sink_x_0_0_0.set_line_label(i, "Data {0}".format(i))
            else:
                self.qtgui_time_sink_x_0_0_0.set_line_label(i, labels[i])
            self.qtgui_time_sink_x_0_0_0.set_line_width(i, widths[i])
            self.qtgui_time_sink_x_0_0_0.set_line_color(i, colors[i])
            self.qtgui_time_sink_x_0_0_0.set_line_style(i, styles[i])
            self.qtgui_time_sink_x_0_0_0.set_line_marker(i, markers[i])
            self.qtgui_time_sink_x_0_0_0.set_line_alpha(i, alphas[i])

        self._qtgui_time_sink_x_0_0_0_win = sip.wrapinstance(self.qtgui_time_sink_x_0_0_0.qwidget(), Qt.QWidget)
        self.top_grid_layout.addWidget(self._qtgui_time_sink_x_0_0_0_win, 0, 0, 1, 1)
        for r in range(0, 1):
            self.top_grid_layout.setRowStretch(r, 1)
        for c in range(0, 1):
            self.top_grid_layout.setColumnStretch(c, 1)
        self._frequency_range = Range(0, (500 - 2), 1, 0, 200)
        self._frequency_win = RangeWidget(self._frequency_range, self.set_frequency, "'frequency'", "counter_slider", int, QtCore.Qt.Horizontal)
        self.top_layout.addWidget(self._frequency_win)
        self.epy_block_1_0 = epy_block_1_0.TriangleWaveGenerator(start_p=0, end_p=3, sample_rate=DAC_sample_rate, freq=DAC_frequency, enable=generate_signal)
        self.epy_block_0_0_1 = epy_block_0_0_1.ADIBlock(portNumber=10, mode=3)
        self.epy_block_0 = epy_block_0.ADIBlock(portNumber=7, mode=20)
        self.blocks_null_source_0 = blocks.null_source(gr.sizeof_float*1)
        self.blocks_null_sink_0_1 = blocks.null_sink(gr.sizeof_float*1)
        self.blocks_null_sink_0_0 = blocks.null_sink(gr.sizeof_float*1)
        self.blocks_null_sink_0 = blocks.null_sink(gr.sizeof_float*1)
        self.analog_sig_source_x_0_0 = analog.sig_source_f(samp_rate, analog.GR_SIN_WAVE, 10000, 1, 0, 0)
        self.analog_sig_source_x_0 = analog.sig_source_f(samp_rate, analog.GR_SIN_WAVE, 1000, 1, 0, 0)


        ##################################################
        # Connections
        ##################################################
        self.connect((self.analog_sig_source_x_0, 0), (self.epy_block_0, 0))
        self.connect((self.analog_sig_source_x_0_0, 0), (self.epy_block_0, 1))
        self.connect((self.blocks_null_source_0, 0), (self.epy_block_0_0_1, 1))
        self.connect((self.blocks_null_source_0, 0), (self.epy_block_0_0_1, 0))
        self.connect((self.epy_block_0, 0), (self.blocks_null_sink_0, 0))
        self.connect((self.epy_block_0, 1), (self.blocks_null_sink_0_0, 0))
        self.connect((self.epy_block_0_0_1, 0), (self.qtgui_time_sink_x_0_0_0, 0))
        self.connect((self.epy_block_0_0_1, 1), (self.qtgui_time_sink_x_0_0_0, 1))
        self.connect((self.epy_block_1_0, 0), (self.blocks_null_sink_0_1, 0))


    def closeEvent(self, event):
        self.settings = Qt.QSettings("GNU Radio", "default")
        self.settings.setValue("geometry", self.saveGeometry())
        self.stop()
        self.wait()

        event.accept()

    def get_frequency(self):
        return self.frequency

    def set_frequency(self, frequency):
        self.frequency = frequency
        self.set_DAC_frequency(((int)(self.DAC_sample_rate /(500 -  self.frequency))))

    def get_DAC_sample_rate(self):
        return self.DAC_sample_rate

    def set_DAC_sample_rate(self, DAC_sample_rate):
        self.DAC_sample_rate = DAC_sample_rate
        self.set_DAC_frequency(((int)(self.DAC_sample_rate /(500 -  self.frequency))))
        self.epy_block_1_0.sample_rate = self.DAC_sample_rate

    def get_samp_rate(self):
        return self.samp_rate

    def set_samp_rate(self, samp_rate):
        self.samp_rate = samp_rate
        self.analog_sig_source_x_0.set_sampling_freq(self.samp_rate)
        self.analog_sig_source_x_0_0.set_sampling_freq(self.samp_rate)

    def get_generate_signal(self):
        return self.generate_signal

    def set_generate_signal(self, generate_signal):
        self.generate_signal = generate_signal
        self.epy_block_1_0.enable = self.generate_signal

    def get_DAC_frequency(self):
        return self.DAC_frequency

    def set_DAC_frequency(self, DAC_frequency):
        self.DAC_frequency = DAC_frequency
        Qt.QMetaObject.invokeMethod(self._DAC_frequency_label, "setText", Qt.Q_ARG("QString", str(self._DAC_frequency_formatter(self.DAC_frequency))))
        self.epy_block_1_0.freq = self.DAC_frequency




def main(top_block_cls=default, options=None):

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