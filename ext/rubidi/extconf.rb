# frozen_string_literal: true

require "mkmf"

pkg_config("fribidi")
create_makefile("rubidi/rubidi")
