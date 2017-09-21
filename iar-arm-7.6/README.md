# grbl1.1f-stm32f103c8
grbl1.1f for stm32

  依照github上的样例移植了grbl1.1，原项目为"https://github.com/MaxwellXyao/GRBL-0.9j-for-STM32".我所做的改动有：
  1.版本号提示为1.1f.
  2.修改了端口定义，需要注意!
  3.将串口通讯改为usb虚拟串口，充分利用stm32f103的特性.
  4.修复一些bug
  
  有许多功能未验证，如限位等
  
  有问题的话请联系tuoqiang@outlook.com


  On github there are some people doing the similar work.This project is based on "https://github.com/MaxwellXyao/GRBL-0.9j-for-STM32".
  Compared to their work,I changed some features:
  1.GRBL version to 1.1f20170801.
  2.CPU map changed,warning!
  3.Changed UART to USB virtual COM port to make full use of stm32f10x.
  4.Fix some bugs.

  However there are some functions I did't transplant or test,such as limit,STEP_PULSE_DELAY and so on.
  
  If you have some issues,you can contact tuoqiang@outlook.com
  
  
