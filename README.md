# Systems and Networks II

## Project 1

Contributors: Ari Palanjian

* Note: This program was developed using WSL and tested using the Google Chrome Browser

## Included Files

- assets
    - screencaps
        - 404notfound.png
        - clientclose.png
        - clientmessage.png
        - exrun.png
        - homepage.png
        - picture.png
    - img.jpg
- templates
    - index.html
    - testPresence.html
- main.cpp
- Makefile
- protocol.pdf
- README.md
- server.cpp
- server.hpp

## How to Run
1. Compile program by entering ```make``` in CLI in the same directory as main.
2. Execute the program by running ```./server <portno>```.
3. In a new browser tab type ```localhost:<portno>```.

## Usage
- Upon entering the address in the browser a get request is sent to the server for /index.html.
- From the homepage you may follow either hyperlinks, enter a message, close the client connection, or close the server.

![Homepage](assets/screencaps/homepage.png?raw=true)

- Clicking on the "Click on this link for an image. " hyperlink redirects to /testPresence.html.

![TestPresence](assets/screencaps/picture.png?raw=true)

- Clicking on the "click here to test the non-existent link " hyperlink redirects to a 404 page.
- Any other GET request other than those outlined in the protocol document will also lead to a 404.

![404NotFound](assets/screencaps/404notfound.png?raw=true)

- The browser client may send a text message to the server which will then print the message to the screen.

![ClientMessage](assets/screencaps/clientmessage.png?raw=true)

- The user may also end the client connection or close the server using the buttons provided resulting in the browser displaying an ERR_EMPTY_RESPONSE.

![NotWorking](assets/screencaps/clientclose.png?raw=true)

* Note: The process will close the client connection after 180 seconds if nothing has been recieved from the server and will remain open for new connections.

## Example Server Run

- The following image shows what the server output may look like depending on the order of actions taken.

![ExRun](assets/screencaps/exrun.png?raw=true)

