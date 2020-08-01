![Logo](http://svg.wiersma.co.za/github/project?lang=cpp&title=Door%20Sensor&tag=garage%20door%20sensor)

This project is an attempt to determine and communicate the state of a rollup
garage door.

It determines the position of the door by checking if the closed
limit wire is pulled to ground. It communicates with a Sonoff Bridge via RF433
transmitter.

While simple, it has proven to be quiet effective. It is important not to make
the open and closed codes too similar, as distortion can occur.
