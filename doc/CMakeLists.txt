project(UgaritManual NONE)
cmake_minimum_required(VERSION 3.11)

find_package(LATEX)
if(LATEX_FOUND)
	if(LUALATEX__FOUND)
		message(STATUS "lualatex found - ${LUALATEX_COMPILER}")
	endif()
	if(BIBTEX_FOUND)
		message(STATUS "bibtex found - ${BIBTEX_COMPILER}")
	endif()
	if(XELATEX_FOUND)
		message(STATUS "xelatex found - ${XELATEX_COMPILER}")
	endif()
	if(PDFLATEX_FOUND)
		message(STATUS "pdfLaTeX found - ${PDFLATEX_COMPILER}")
	endif()
	if(BIBER_FOUND)
		message(STATUS "biber found - ${BIBER_COMPILER}")
	endif()
	if(MAKEINDEX_FOUND)
		message(STATUS "makeindex found - ${MAKEINDEX_COMPILER}")
	endif()
else()
	message(ERROR "No latex tools found!")
endif()

# The directory where the final build data will be stored.
set(LATEX_OUTPUT_PATH "${CMAKE_CURRENT_BINARY_DIR}")
set(OUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}")
# The source file containing the reference for cites.
set(BIB_REFERENCE_PATH ${CMAKE_SOURCE_DIR}/doc.bib)

# Directory where the source files are located.
set( WORKINGDIR "${CMAKE_CURRENT_BINARY_DIR}" )

# Latex source file.
set( MAIN_TEX_BASE_FILENAME "doc")
set( MAIN_TEX "${CMAKE_CURRENT_SOURCE_DIR}/${MAIN_TEX_BASE_FILENAME}.tex")
set( MAIN_IDX "${OUT_DIRECTORY}/${MAIN_TEX_BASE_FILENAME}.idx")
set( MAIN_AUX "${OUT_DIRECTORY}/${MAIN_TEX_BASE_FILENAME}.aux")
set( MAIN_BCF "${OUT_DIRECTORY}/${MAIN_TEX_BASE_FILENAME}.bcf")

# First pass.
add_custom_target( latex-prebuild
		COMMAND ${XELATEX_COMPILER}  -draftmode -interaction=nonstopmode ${MAIN_TEX}
		COMMAND ${XELATEX_COMPILER}  -draftmode -interaction=nonstopmode ${MAIN_TEX}
		COMMENT "Starting Prebuild."
		WORKING_DIRECTORY ${WORKINGDIR}
		DEPENDS ${MAIN_TEX})

# Generate the indices for the index table.
add_custom_target( latex-makeindex
			COMMAND ${MAKEINDEX_COMPILER} doc.idx
			COMMENT "Read and create indices with ${MAIN_IDX}."
            WORKING_DIRECTORY ${WORKINGDIR}
 			DEPENDS ${MAIN_TEX} ${MAIN_IDX})
add_dependencies(latex-makeindex latex-prebuild)


# Generate what citation found in the latex file.
add_custom_target( latex-bibreferences
			COMMAND ${BIBER_COMPILER} ${MAIN_BCF}
 			COMMENT "Read and create main bib references file."
            WORKING_DIRECTORY ${WORKINGDIR}
 			DEPENDS  ${MAIN_TEX})
add_dependencies( latex-bibreferences latex-prebuild)


# Second pass - generate the final pdf.
add_custom_target( latex-pdf	
			COMMAND ${XELATEX_COMPILER} ${MAIN_TEX} 
			WORKING_DIRECTORY ${WORKINGDIR}
			COMMENT "Assembling the final pdf file."
			DEPENDS  ${MAIN_TEX})
add_dependencies( latex-pdf latex-prebuild latex-makeindex latex-bibreferences )

add_custom_target(all-formats ALL) # Entry point of execution.
add_dependencies( all-formats latex-pdf)