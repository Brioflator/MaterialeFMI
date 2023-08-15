import pyautogui, time #pylint: disable=E0401
time.sleep(10)
f=open("lyrics", encoding="utf8")
for word in f:
    pyautogui.typewrite(word)
    pyautogui.press("enter")

