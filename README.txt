
>>This is a CCTV project with face detection.

>>It is a distributed application, which allows to connect a server, 
  on which the acquisition and processing of images is carried out, to different clients.

>>The application uses a TCP/Ip communication protocol.

>>The application uses OpenCV for image processing and faces detection.
  So, please make sure that the development environment you use is configured for Qt and OpenCV.

>>Make sure to choose the paths associated with your OpenCV installation on the server application ( on "Server.pro" )
  For more informations about how to setup Qt and openCV :
  https://wiki.qt.io/OpenCV_with_Qt
  https://wiki.qt.io/How_to_setup_Qt_and_openCV_on_Windows

>>Client connection is controlled by password authentication.
  With a possibility to display and disconnect clients from the server application.
  And thus control access to the server and to the data it broadcasts.

>>The application can be used on a local network or on the internet 
  +Make sure the port you are using is opened
  +Make sure that you allow your application to communicate on the network
  +please make sure that you use the right IP address (global IP for internet communication).

>>The application has been tested for different platforms: Raspberry Pi 4, Windows, Linux, Android.
