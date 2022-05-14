.SILENT: help backup restore
.PHONY: help backup restore

help: 
	echo "makefile"
	echo
	echo "	backup : backup folder (create .bak of $(FOLDER))"
	echo "	restore : restore folder (move .bak to $(FOLDER))"
	echo
	echo "folder = $(FOLDER)"

backup:
	[ -d "$(FOLDER)" ] && cp -r "$(FOLDER)" "$(FOLDER).bak" || echo "Error"

restore:
	[ -d "$(FOLDER).bak" ] && [ ! -d "$(FOLDER)" ] && mv "$(FOLDER).bak" "$(FOLDER)" || echo "Error"

