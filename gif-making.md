### break apart a gif  
    convert -coalesce dVTlQts.gif dVTlQts_%d.gif  

### put together a gif  
    convert -delay 15 -loop 0 some-image.png some-other-image.png thing.gif  
