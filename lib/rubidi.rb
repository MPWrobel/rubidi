# frozen_string_literal: true

require_relative "rubidi/version"
require_relative "rubidi/rubidi"

module Rubidi
  class Error < StandardError; end

  def self.bidi(text)
    text.split("\n").map { |line| Rubidi.bidi_inner(line) }.join("\n")
  end
end
