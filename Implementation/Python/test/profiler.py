*"""
Author: Jacob London

Date Modified: March 4, 2019
"""

import time

class Profiler(object):

    def __init__(self):
        self.times = []
        self.start = time.time()

    def mark(self, name):
        self.times.append((name, time.time()))
    
    def display(self):

        total = time.time() - self.start
        print('\nTotal:', total, 'sec')

        # find the time for each individual step
        for index in range(len(self.times)):
            name = self.times[index][0] + ' time:'
            duration = self.times[index][1]

            # find the differences b/w the current/prev times for cumulative
            if index == 0:
                prev_time = self.start
            else:
                prev_time = self.times[index - 1][1]
            
            # get cumulative time, and total percent that time was
            cumulative = duration - prev_time
            percentage = cumulative / total * 100

            print(name, cumulative, 'sec\n', percentage, '%')

        print()