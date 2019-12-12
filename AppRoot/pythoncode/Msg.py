# -*- coding: ANSI -*-
class Msg:
    def __init__(self, argv):
        self.g = argv[1]
        self.q = argv[2]
        self.id = argv[3]
        self.text  = ''
        for each in argv[4:]:
            self.text = self.text + each + ' '
        self.text = self.text[:-1]
