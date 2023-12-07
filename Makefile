src_dir := ./platform/fileoperation/source ./app

c_srcs := $(shell ls ./app/*.c)
c_objs := $(subst .c,.o,$(c_srcs))
c_objs := $(subst app/,output/,$(c_objs))

app_c_srcs := $(shell ls ./platform/fileoperation/source/*.c)
app_c_objs := $(subst .c,.o,$(app_c_srcs))
app_c_objs := $(subst /platform/fileoperation/source/,output/,$(app_c_objs))
# 获取所有的c文件以及需要生成的.o文件
c_objs += $(app_c_objs)
c_srcs += $(app_c_srcs)


in_path := ./inc ./platform/fileoperation/inc
I_flags := $(foreach item,$(in_path),-I$(item))

compile_option := -g -O1 -w $(I_flags)

clean :
	@rm output/*

output/result : $(c_srcs)
	@mkdir -p $(dir $@)
	@gcc $^ -o $@ $(compile_option)

run : output/result
	@./output/result

compile : output/result

debug:
	@echo $(app_c_srcs)

.PHONY : debug compile clean
