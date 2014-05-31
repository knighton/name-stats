CC=clang++
FLAGS=-Wall -O3 `pkg-config --cflags --libs protobuf,libgflags` -fcolor-diagnostics

all: run_stats_mgr

run_stats_mgr:
	$(CC) base/data_cube.cc base/file_util.cc base/line_reader.cc base/object_store.cc base/string_util.cc run_stats_mgr.cc -o run_stats_mgr $(FLAGS)

clean:
	rm -f run_stats_mgr
